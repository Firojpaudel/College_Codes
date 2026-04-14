package Unit_1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class StudentRecordAnalysis {
    public static void main(String[] args) {
        String fileName = "resources/student_records.txt";
        double highestMarks = -1;
        double totalMarks = 0;
        int studentCount = 0;

        System.out.println("--- Student Record Analysis ---");

        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                // Format: Name,Marks
                String[] parts = line.split(",");
                if (parts.length >= 2) {
                    try {
                        double marks = Double.parseDouble(parts[1].trim());
                        
                        // i. Track highest marks
                        if (marks > highestMarks) {
                            highestMarks = marks;
                        }
                        
                        totalMarks += marks;
                        studentCount++;
                    } catch (NumberFormatException e) {
                        System.err.println("Skipping malformed marks: " + line);
                    }
                }
            }

            if (studentCount > 0) {
                // ii. Calculate average marks
                double average = totalMarks / studentCount;

                System.out.println("Total Students: " + studentCount);
                System.out.println("Highest Marks:  " + highestMarks);
                System.out.printf("Average Marks:  %.2f\n", average);
            } else {
                System.out.println("No valid records found in the file.");
            }

        } catch (IOException e) {
            System.err.println("Fatal Error: Could not read file. " + e.getMessage());
        }
    }
}
