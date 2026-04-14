package Unit_1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class WordReplaceDemo {
    public static void main(String[] args) {
        String inputFileName = "resources/analysis_input.txt";
        String outputFileName = "resources/replaced_output.txt";

        Scanner scanner = new Scanner(System.in);

        System.out.println("--- Word Replacement Program ---");

        System.out.print("Enter word to find: ");
        String findWord = scanner.nextLine();

        System.out.print("Enter replacement word: ");
        String replaceWord = scanner.nextLine();

        System.out.println("Replacing '" + findWord + "' with '" + replaceWord + "'...");

        int replacementCount = 0;

        try (
                BufferedReader reader = new BufferedReader(new FileReader(inputFileName));
                BufferedWriter writer = new BufferedWriter(new FileWriter(outputFileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                int index = 0;
                while ((index = line.indexOf(findWord, index)) != -1) {
                    replacementCount++;
                    index += findWord.length();
                }

                String modifiedLine = line.replace(findWord, replaceWord);
                writer.write(modifiedLine);
                writer.newLine();
            }

            System.out.println("\nSUCCESS!");
            System.out.println("Total replacements made: " + replacementCount);
            System.out.println("Result saved to: " + outputFileName);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
