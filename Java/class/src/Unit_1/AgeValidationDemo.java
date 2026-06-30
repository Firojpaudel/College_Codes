package Unit_1;

public class AgeValidationDemo {
    // a. Method to validate age
    public static void checkAge(int age) {
        if (age < 18) {
            // b. Throw exception if age < 18
            throw new ArithmeticException("Access denied - You must be at least 18 years old.");
        } else {
            System.out.println("Access granted - You are " + age + " years old.");
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Age Validation Test ---");

        // Test with invalid age
        try {
            System.out.println("Checking age 15...");
            checkAge(15);
        } catch (ArithmeticException e) {
            System.out.println("Exception Caught: " + e.getMessage());
        }

        // Test with valid age
        try {
            System.out.println("\nChecking age 20...");
            checkAge(20);
        } catch (ArithmeticException e) {
            System.out.println("Exception Caught: " + e.getMessage());
        }
    }
}