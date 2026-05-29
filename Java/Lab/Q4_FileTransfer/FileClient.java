import java.io.*;
import java.net.Socket;

public class FileClient {
    public static void main(String[] args) {
        // Assume file 'to_send.txt' exists.
        File fileToSend = new File("to_send.txt");
        try {
            fileToSend.createNewFile(); // Just for demonstration if it doesn't exist
            try (FileWriter fw = new FileWriter(fileToSend)) {
                fw.write("This is a test file for File Transfer protocol.\n");
            }
        } catch(IOException e){}

        try (Socket socket = new Socket("localhost", 8081)) {
            FileInputStream fileIn = new FileInputStream(fileToSend);
            OutputStream out = socket.getOutputStream();

            byte[] buffer = new byte[8192];
            int bytesRead;
            while ((bytesRead = fileIn.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }

            System.out.println("File transfer complete.");
            fileIn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
