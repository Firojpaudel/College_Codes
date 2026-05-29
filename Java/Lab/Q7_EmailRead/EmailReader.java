import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.mail.*;

public class EmailReader {
    private static final Logger logger = Logger.getLogger(EmailReader.class.getName());

    public static void main(String[] args) {
        final String username = "firoj7902@mbmcsit.edu.np";
        final String password = "xxxx xxxx xxxx xxxx";

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

            logger.info("Reading top " + (total - start) + " latest emails...");
            for (int i = total - 1; i >= start; i--) {
                Message msg = messages[i];
                logger.info("---------------------------------");
                logger.info("From: " + msg.getFrom()[0]);
                logger.info("Subject: " + msg.getSubject());
                logger.info("Date: " + msg.getSentDate());
            }

            inbox.close(false);
            store.close();
        } catch (Exception e) {
            logger.log(Level.SEVERE, "An error occurred while reading emails.", e);
        }
    }
}
