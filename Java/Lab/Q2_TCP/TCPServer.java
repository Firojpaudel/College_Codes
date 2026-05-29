import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is waiting for client on port 8080...");
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected!");

            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();

            byte[] buffer = new byte[1024];
            int bytesRead = input.read(buffer);
            String message = new String(buffer, 0, bytesRead);
            System.out.println("Received from client: " + message);

            String reply = "Message received successfully!";
            output.write(reply.getBytes());

            clientSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
