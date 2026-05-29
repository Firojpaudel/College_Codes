import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.mail.*;
import javax.mail.internet.*;

public class EmailSender {
    private static final Logger logger = Logger.getLogger(EmailSender.class.getName());

    public static void main(String[] args) {
        String to = "ujjwalpuri221@gmail.com";
        String from = "firoj7902@mbmcsit.edu.np";
        final String username = "firoj7902@mbmcsit.edu.np";
        final String password = "xxxx xxxx xxxx xxxx"; 

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
            logger.info("Preparing to send email to " + to + "...");
            
            String emailSubject = "Test Email Subject";
            String emailBody = "This is a test message body sent via JavaMail.";
            
            logger.info("Subject: " + emailSubject);
            logger.info("Content: " + emailBody);

            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress(from));
            message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(to));
            message.setSubject(emailSubject);
            message.setText(emailBody);

            Transport.send(message);
            logger.info("Email Sent Successfully to " + to + "!");
        } catch (MessagingException e) {
            logger.log(Level.SEVERE, "Failed to send email.", e);
        }
    }
}