package Unit_1;

import java.util.Scanner;

public class ResourceClosingDemo {
    public static void main(String[] args) {
        // a. Create a Scanner object to read input
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("Enter your name: ");
            String name = scanner.nextLine();

            System.out.print("Enter your age: ");
            int age = scanner.nextInt();

            System.out.println("\n--- User Details ---");
            System.out.println("Name: " + name);
            System.out.println("Age: " + age);

        } catch (Exception e) {
            System.out.println("Error reading input: " + e.getMessage());
        } finally {
            // b. Use finally block to ensure the resource (scanner) is closed
            System.out.println("\nFinally block: Closing the Scanner resource safely.");
            scanner.close();
        }
    }
}