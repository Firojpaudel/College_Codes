package Unit_1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class WordSortDemo {
    public static void main(String[] args) {
        String fileName = "resources/analysis_input.txt";
        ArrayList<String> wordList = new ArrayList<>();

        System.out.println("--- Reading words from: " + fileName + " ---");

        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                // Split by non-alphanumeric characters to get words
                String[] lineWords = line.split("[^a-zA-Z0-9]+");
                for (String word : lineWords) {
                    if (!word.trim().isEmpty()) {
                        wordList.add(word.trim());
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        if (wordList.isEmpty()) {
            System.out.println("No words found in the file.");
            return;
        }

        // Convert ArrayList to String array for manual sorting
        String[] words = wordList.toArray(new String[0]);

        System.out.println("Total words found: " + words.length);
        System.out.println("Sorting words alphabetically...");

        // Manual Alphabetical Sort (Bubble Sort)
        // Comparing strings using compareToIgnoreCase for natural alphabetical order
        for (int i = 0; i < words.length - 1; i++) {
            for (int j = 0; j < words.length - i - 1; j++) {
                if (words[j].compareToIgnoreCase(words[j + 1]) > 0) {
                    // Swap words[j] and words[j+1]
                    String temp = words[j];
                    words[j] = words[j + 1];
                    words[j + 1] = temp;
                }
            }
        }

        System.out.println("\n--- Sorted Words ---");
        for (int i = 0; i < words.length; i++) {
            System.out.print(words[i] + (i == words.length - 1 ? "" : ", "));
            // New line every 8 words for readability
            if ((i + 1) % 8 == 0)
                System.out.println();
        }
        System.out.println("\n");
    }
}
