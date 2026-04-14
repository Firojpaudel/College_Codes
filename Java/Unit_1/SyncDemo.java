package Unit_1;

class SharedCounter {
    int count = 0;

    // b. Use 'synchronized' to ensure only one thread increments at a time
    public synchronized void increment() {
        count++;
    }
}

public class SyncDemo {
    public static void main(String[] args) throws InterruptedException {
        SharedCounter shared = new SharedCounter();

        // a. Creating two threads that increment the same counter
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) shared.increment();
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) shared.increment();
        });

        System.out.println("Threads starting to increment...");
        
        t1.start();
        t2.start();

        // Wait for both threads to finish
        t1.join();
        t2.join();

        System.out.println("Final shared counter value: " + shared.count);
        System.out.println("(Expected: 2000)");
    }
}
