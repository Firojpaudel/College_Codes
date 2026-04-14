package Unit_1;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class FileCompareDemo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("--- File Comparison Utility ---");

        System.out.print("Enter first filename: ");
        String file1Path = scanner.nextLine();

        System.out.print("Enter second filename: ");
        String file2Path = scanner.nextLine();

        try {
            if (areFilesIdentical(file1Path, file2Path)) {
                System.out.println("\nRESULT: The files are IDENTICAL.");
            } else {
                System.out.println("\nRESULT: The files are DIFFERENT.");
            }
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }

    private static boolean areFilesIdentical(String path1, String path2) throws IOException {
        File file1 = new File(path1);
        File file2 = new File(path2);

        if (!file1.exists() || !file2.exists()) {
            throw new IOException("One or both files do not exist.");
        }

        if (file1.length() != file2.length()) {
            return false;
        }

        try (BufferedInputStream bis1 = new BufferedInputStream(new FileInputStream(file1));
             BufferedInputStream bis2 = new BufferedInputStream(new FileInputStream(file2))) {
            
            int b1, b2;
            while ((b1 = bis1.read()) != -1) {
                b2 = bis2.read();
                if (b1 != b2) {
                    return false;
                }
            }
        }
        return true;
    }
}
