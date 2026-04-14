package Unit_1;

import java.io.IOException;
import java.io.RandomAccessFile;

public class RandomAccessDemo {
    public static void main(String[] args) {
        String fileName = "resources/students.dat";

        try (RandomAccessFile raf = new RandomAccessFile(fileName, "rw")) {
            // a. Store student records
            System.out.println("Writing student records...");
            
            // Record 1 (Student ID 1, Marks 85.5)
            raf.writeInt(1);      // 4 bytes
            raf.writeDouble(85.5); // 8 bytes

            // Capture the exact pointer where the second record starts
            long pointerPosition = raf.getFilePointer();

            // Record 2 (Student ID 2, Marks 92.0)
            raf.writeInt(2); 
            raf.writeDouble(92.0);

            // b. Access a specific record using the file pointer
            System.out.println("Jumping to the second student's record using seek()...");
            raf.seek(pointerPosition); // Seeks to the captured position

            int id = raf.readInt();
            double marks = raf.readDouble();

            System.out.println("\n--- Accessed Record ---");
            System.out.println("Student ID: " + id);
            System.out.println("Marks: " + marks);

        } catch (IOException e) {
            System.out.println("Error processing binary file: " + e.getMessage());
        }
    }
}
