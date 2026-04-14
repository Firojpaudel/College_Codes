package Unit_1;

public class MethodOverloading {

    // a. Sum of 2 integers
    public static int sum(int a, int b) {
        return a + b;
    }

    // b. Sum of 3 integers
    public static int sum(int a, int b, int c) {
        return a + b + c;
    }

    // c. Sum of array elements
    public static int sum(int[] arr) {
        int total = 0;
        for (int num : arr) {
            total += num;
        }
        return total;
    }

    public static void main(String[] args) {
        // Testing sum of 2 integers
        System.out.println("Sum of 10 and 20: " + sum(10, 20));

        // Testing sum of 3 integers
        System.out.println("Sum of 10, 20 and 30: " + sum(10, 20, 30));

        // Testing sum of array
        int[] myNumbers = {1, 2, 3, 4, 5};
        System.out.println("Sum of array {1, 2, 3, 4, 5}: " + sum(myNumbers));
    }
}
