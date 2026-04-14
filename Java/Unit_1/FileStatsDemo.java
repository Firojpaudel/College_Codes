package Unit_1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileStatsDemo {
    public static void main(String[] args) {
        String fileName = "resources/input.txt";
        int lineCount = 0;
        int wordCount = 0;

        System.out.println("--- File Word & Line Counter ---");

        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;

            // a. Read the text file line by line
            while ((line = br.readLine()) != null) {
                lineCount++; // Increment line count
                
                // b. Count words in the line
                if (!line.trim().isEmpty()) {
                    // Split by whitespace to find individual words
                    String[] words = line.trim().split("\\s+");
                    wordCount += words.length;
                }
            }

            System.out.println("Processing file: " + fileName);
            System.out.println("Total Lines: " + lineCount);
            System.out.println("Total Words: " + wordCount);

        } catch (IOException e) {
            System.err.println("Error: Could not read file. " + e.getMessage());
        }
    }
}
