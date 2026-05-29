import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class TCPClient {
    public static void main(String[] args) {
        try (Socket socket = new Socket("localhost", 8080)) {
            OutputStream output = socket.getOutputStream();
            InputStream input = socket.getInputStream();

            String message = "Hello Server!";
            output.write(message.getBytes());
            System.out.println("Message sent to server.");

            byte[] buffer = new byte[1024];
            int bytesRead = input.read(buffer);
            String response = new String(buffer, 0, bytesRead);
            System.out.println("Server reply: " + response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
