package Unit_1;

class Counter {
    int count = 0;

    // a. UNSAFE Method: This will cause a Race Condition because it's not
    // synchronized
    public void unsafeIncrement() {
        count++;
    }

    // b. SAFE Method: Fixed using the 'synchronized' keyword
    public synchronized void safeIncrement() {
        count++;
    }
}

public class RaceConditionDemo {
    public static void main(String[] args) throws InterruptedException {
        int iterations = 100000; // Large number of increments to trigger the race

        System.out.println("Running increments with 2 threads (" + iterations + " each)...");

        // --- SECTION 1: DEMONSTRATING RACE CONDITION ---
        Counter unsafeCounter = new Counter();
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < iterations; i++)
                unsafeCounter.unsafeIncrement();
        });
        Thread t2 = new Thread(() -> {
            for (int i = 0; i < iterations; i++)
                unsafeCounter.unsafeIncrement();
        });

        t1.start();
        t2.start();
        t1.join();
        t2.join();

        System.out.println("\n1. WITHOUT Synchronization (Race Condition):");
        System.out.println("   Expected Count: " + (iterations * 2));
        System.out.println("   Actual Count:   " + unsafeCounter.count);

        // --- SECTION 2: FIXING WITH SYNCHRONIZED ---
        Counter safeCounter = new Counter();
        Thread t3 = new Thread(() -> {
            for (int i = 0; i < iterations; i++)
                safeCounter.safeIncrement();
        });
        Thread t4 = new Thread(() -> {
            for (int i = 0; i < iterations; i++)
                safeCounter.safeIncrement();
        });

        t3.start();
        t4.start();
        t3.join();
        t4.join();

        System.out.println("\n2. WITH Synchronization (Fixed):");
        System.out.println("   Expected Count: " + (iterations * 2));
        System.out.println("   Actual Count:   " + safeCounter.count);
    }
}
