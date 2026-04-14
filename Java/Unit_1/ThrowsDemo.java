package Unit_1;

public class ThrowsDemo {

    // a. Method declares that it may throw an Exception using 'throws'
    public static void checkData(int value) throws Exception {
        if (value < 0) {
            throw new Exception("Negative values are not allowed!");
        } else {
            System.out.println("Value processed: " + value);
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 'throws' Keyword Demo ---");

        // b. The caller (main method) handles the exception using try-catch
        try {
            checkData(50); // This will work
            checkData(-10); // This will throw an exception
        } catch (Exception e) {
            System.out.println("Exception handled in main: " + e.getMessage());
        }

        System.out.println("\nExecution completed.");
    }
}