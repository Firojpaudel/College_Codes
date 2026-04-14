package Unit_1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class TextAnalysisDemo {

    public static void main(String[] args) {
        String fileName = "resources/analysis_input.txt";
        String searchWord = "Java"; // vii. Word to search for

        int vowels = 0, consonants = 0, digits = 0;
        int startsWithVowelCount = 0;
        String longestWord = "";
        Map<String, Integer> frequencyMap = new HashMap<>();
        StringBuilder palindromes = new StringBuilder();

        try {
            Scanner fileScanner = new Scanner(new File(fileName));

            // a. Read from file
            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();

                // c. i, ii, iii: Count Vowels, Consonants, Digits
                for (char c : line.toCharArray()) {
                    if (Character.isDigit(c)) {
                        digits++;
                    } else if (Character.isLetter(c)) {
                        if (isVowel(c)) vowels++;
                        else consonants++;
                    }
                }

                // b. Tokenize words for further analysis
                // Using regex to split by non-alphanumeric characters
                String[] words = line.split("[^a-zA-Z0-9]+");

                for (String word : words) {
                    if (word.isEmpty()) continue;

                    // b. Find Palindromes
                    if (isPalindrome(word)) {
                        palindromes.append(word).append(" ");
                    }

                    // c. iv: Count words starting with vowels
                    if (isVowel(word.charAt(0))) {
                        startsWithVowelCount++;
                    }

                    // c. v: Word Frequency
                    String lowerWord = word.toLowerCase();
                    frequencyMap.put(lowerWord, frequencyMap.getOrDefault(lowerWord, 0) + 1);

                    // c. vi: Longest Word
                    if (word.length() > longestWord.length()) {
                        longestWord = word;
                    }
                }
            }
            fileScanner.close();

            // e. Display result
            System.out.println("--- TEXT ANALYSIS REPORT ---");
            System.out.println("File Name: " + fileName);
            System.out.println("\n[Character Counts]");
            System.out.println("Vowels:      " + vowels);
            System.out.println("Consonants:  " + consonants);
            System.out.println("Digits:      " + digits);

            System.out.println("\n[Word Analysis]");
            System.out.println("Palindromes:        " + (palindromes.length() > 0 ? palindromes : "None"));
            System.out.println("Starts with Vowel:  " + startsWithVowelCount);
            System.out.println("Longest Word:       " + longestWord);
            
            // c. vii: Search result
            System.out.println("Search for '" + searchWord + "': " + 
                (frequencyMap.containsKey(searchWord.toLowerCase()) ? "FOUND" : "NOT FOUND"));

            System.out.println("\n[Word Frequencies]");
            for (Map.Entry<String, Integer> entry : frequencyMap.entrySet()) {
                System.out.printf("%-15s : %d\n", entry.getKey(), entry.getValue());
            }

        } catch (FileNotFoundException e) {
            System.err.println("Error: Input file not found. " + e.getMessage());
        }
    }

    private static boolean isVowel(char c) {
        char lower = Character.toLowerCase(c);
        return "aeiou".indexOf(lower) != -1;
    }

    private static boolean isPalindrome(String s) {
        if (s.length() < 2) return false; // Single letters aren't typically counted
        String rev = new StringBuilder(s).reverse().toString();
        return s.equalsIgnoreCase(rev);
    }
}
