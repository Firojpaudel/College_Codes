package Unit_1;

public class LoopComparison {
    public static void main(String[] args) {
        // Initializing two identical arrays
        int[] traditionalArr = {1, 2, 3, 4, 5};
        int[] forEachArr = {1, 2, 3, 4, 5};

        System.out.println("--- Array Modification Comparison ---");
        
        // 1. Traditional for loop: Modifying elements
        System.out.println("\n1. Using Traditional For Loop (arr[i] *= 10):");
        for (int i = 0; i < traditionalArr.length; i++) {
            traditionalArr[i] = traditionalArr[i] * 10;
        }
        printArray(traditionalArr);
        System.out.println("Result: Elements ARE modified.");

        // 2. For-each loop: Attempting to modify elements
        System.out.println("\n2. Using For-Each Loop (num *= 10):");
        for (int num : forEachArr) {
            num = num * 10; // This only changes the local 'num' variable, not the array element
        }
        printArray(forEachArr);
        System.out.println("Result: Elements ARE NOT modified.");
        
        System.out.println("\nConclusion: Use traditional loops if you need to modify array elements. Use for-each loops for read-only operations.");
    }

    // Helper method to print array
    public static void printArray(int[] arr) {
        System.out.print("Array state: ");
        for (int val : arr) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
}
