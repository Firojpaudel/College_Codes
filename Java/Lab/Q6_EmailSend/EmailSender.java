import java.util.Properties;
import javax.mail.*;
import javax.mail.internet.*;

public class EmailSender {
    public static void main(String[] args) {
        String to = "receiver@example.com";
        String from = "your-email@example.com";
        final String username = "your-email@example.com";
        final String password = "your-app-password"; // Use App Password if Gmail

        Properties props = new Properties();
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");

        Session session = Session.getInstance(props, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication(username, password);
            }
        });

        try {
            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress(from));
            message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(to));
            message.setSubject("Test Email Subject");
            message.setText("This is a test message body sent via JavaMail.");

            Transport.send(message);
            System.out.println("Email Sent Successfully!");
        } catch (MessagingException e) {
            System.out.println("Failed to send email.");
            e.printStackTrace();
        }
    }
}