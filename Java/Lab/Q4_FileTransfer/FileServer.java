import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class FileServer {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8081)) {
            System.out.println("File Server running on port 8081...");
            Socket socket = serverSocket.accept();
            System.out.println("Client connected!");

            InputStream in = socket.getInputStream();
            FileOutputStream fileOut = new FileOutputStream("received_file.txt");

            byte[] buffer = new byte[8192];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                fileOut.write(buffer, 0, bytesRead);
            }

            System.out.println("File received and saved as 'received_file.txt'");
            fileOut.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
