package Unit_1;

public class ArraySum {
    public static void main(String[] args) {
        // Initialize an array
        int[] numbers = {10, 20, 30, 40, 50};
        int sum = 0;

        // Display the array elements
        System.out.print("Array: ");
        for (int num : numbers) {
            System.out.print(num + " ");
        }

        // Calculate sum using for-each loop
        for (int num : numbers) {
            sum += num;
        }

        // Print the result
        System.out.println("\n\nSum of array elements: " + sum);
    }
}
