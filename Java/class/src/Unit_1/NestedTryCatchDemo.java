package Unit_1;

public class NestedTryCatchDemo {
    public static void main(String[] args) {
        System.out.println("--- Nested Try-Catch Demo ---");

        try {
            // Outer Try Block: Handling Array Exception
            int[] numbers = {10, 20, 30};

            try {
                // Inner Try Block: Handling Arithmetic Exception
                int result = numbers[1] / 0;
                System.out.println("Division result: " + result);

            } catch (ArithmeticException e) {
                System.out.println("Inner Catch Handled: " + e.getMessage());
            }

            // This line is back in the outer try block
            System.out.println("Accessing invalid index: " + numbers[10]);

        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Outer Catch Handled: " + e.getMessage());
        }

        System.out.println("Program completed normally.");
    }
}
