package Unit_1;

import java.util.Arrays;

public class FrequencyCounter {

    public static void main(String[] args) {
        // Sample array
        int[] arr = { 1, 2, 8, 3, 2, 2, 2, 5, 1 };

        System.out.println("Original Array: " + Arrays.toString(arr));
        System.out.println("---------------------------------------");
        System.out.println(" Element | Frequency");
        System.out.println("---------------------------------------");

        findFrequency(arr);
    }

    public static void findFrequency(int[] arr) {
        int n = arr.length;
        int[] frequency = new int[n];
        int visited = -1;

        for (int i = 0; i < n; i++) {
            int count = 1;
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                    // To avoid counting the same element again
                    frequency[j] = visited;
                }
            }
            if (frequency[i] != visited) {
                frequency[i] = count;
            }
        }

        // Display the frequencies
        for (int i = 0; i < frequency.length; i++) {
            if (frequency[i] != visited) {
                System.out.printf("   %-5d |    %d\n", arr[i], frequency[i]);
            }
        }
    }
}