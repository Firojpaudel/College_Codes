import java.util.Properties;
import javax.mail.*;

public class EmailReader {
    public static void main(String[] args) {
        final String username = "your-email@example.com";
        final String password = "your-app-password";

        Properties props = new Properties();
        props.put("mail.store.protocol", "imaps");
        props.put("mail.imaps.host", "imap.gmail.com");
        props.put("mail.imaps.port", "993");

        try {
            Session session = Session.getDefaultInstance(props, null);
            Store store = session.getStore("imaps");
            store.connect("imap.gmail.com", username, password);

            Folder inbox = store.getFolder("INBOX");
            inbox.open(Folder.READ_ONLY);

            Message[] messages = inbox.getMessages();
            int total = messages.length;
            int start = Math.max(0, total - 5);

            System.out.println("Reading top 5 latest emails...");
            for (int i = total - 1; i >= start; i--) {
                Message msg = messages[i];
                System.out.println("---------------------------------");
                System.out.println("From: " + msg.getFrom()[0]);
                System.out.println("Subject: " + msg.getSubject());
                System.out.println("Date: " + msg.getSentDate());
            }

            inbox.close(false);
            store.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
