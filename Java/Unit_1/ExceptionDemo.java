package Unit_1;

public class ExceptionDemo {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30};

        System.out.println("--- Exception Handling Demo ---");

        try {
            // a. Accessing an index that doesn't exist
            // System.out.println("Accessing index 5: " + numbers[5]); 

            // b. Dividing by zero
            int result = numbers[0] / 0;
            System.out.println("Result: " + result);

        } catch (ArithmeticException e) {
            // Handles division by zero
            System.out.println("Caught: ArithmeticException (Cannot divide by zero!)");
        } catch (ArrayIndexOutOfBoundsException e) {
            // Handles illegal array access
            System.out.println("Caught: ArrayIndexOutOfBoundsException (Index out of range!)");
        } catch (Exception e) {
            // Catch-all for any other error
            System.out.println("Caught: General Exception - " + e.getMessage());
        } finally {
            System.out.println("Finally: This block always executes.");
        }
        
        System.out.println("\nExecution finished successfully.");
    }
}
