package Unit_1;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCopyDemo {
    public static void main(String[] args) {
        String source = "input.txt";
        String destination = "output.txt";

        System.out.println("--- Byte Stream File Copy ---");

        // Try-with-resources to handle automatic closing of streams
        try (FileInputStream in = new FileInputStream(source);
             FileOutputStream out = new FileOutputStream(destination)) {

            int data;
            // Read one byte at a time
            while ((data = in.read()) != -1) {
                // Write the same byte to the output file
                out.write(data);
            }

            System.out.println("Successfully copied content from " + source + " to " + destination);

        } catch (IOException e) {
            System.out.println("IO Error: " + e.getMessage());
        }
    }
}
