package Unit_1;

public class EvenOddDemo {
    private int counter = 1; // Start from 1
    private final int MAX_LIMIT = 10;

    // Method for printing odd numbers
    public void printOdd() {
        synchronized (this) {
            while (counter <= MAX_LIMIT) {
                // If the number is even, wait for the even thread to print it
                while (counter % 2 == 0) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                    }
                }

                // Print and increment
                if (counter <= MAX_LIMIT) {
                    System.out.println("Odd Thread:  " + counter);
                    counter++;
                    notify(); // Notify the even thread
                }
            }
        }
    }

    // Method for printing even numbers
    public void printEven() {
        synchronized (this) {
            while (counter <= MAX_LIMIT) {
                // If the number is odd, wait for the odd thread to print it
                while (counter % 2 != 0) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                    }
                }

                // Print and increment
                if (counter <= MAX_LIMIT) {
                    System.out.println("Even Thread: " + counter);
                    counter++;
                    notify(); // Notify the odd thread
                }
            }
        }
    }

    public static void main(String[] args) {
        EvenOddDemo demo = new EvenOddDemo();

        // Create two threads
        Thread oddThread = new Thread(demo::printOdd);
        Thread evenThread = new Thread(demo::printEven);

        System.out.println("--- Even-Odd Sequence Demo ---");

        // Start threads
        oddThread.start();
        evenThread.start();
    }
}