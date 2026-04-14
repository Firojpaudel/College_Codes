package Unit_1;

class Counter {
    // a. Static variable: shared by all objects, used for counting
    static int count = 0;

    // b. Final variable: constant value, cannot be modified
    final int MAX_LIMIT = 100;

    Counter() {
        count++; // Increment static count every time an object is created
    }

    void show() {
        System.out.println("Object created. Total count so far: " + count);
    }
}

public class StaticFinalDemo {
    public static void main(String[] args) {
        // Create 3 objects
        Counter c1 = new Counter();
        Counter c2 = new Counter();
        Counter c3 = new Counter();

        System.out.println("--- Static Variable Demo ---");
        System.out.println("Final count (should be 3): " + Counter.count);

        System.out.println("\n--- Final Variable Demo ---");
        Counter c = new Counter();
        System.out.println("Constant MAX_LIMIT value: " + c.MAX_LIMIT);

        // Demonstating that final variable cannot be changed
        // c.MAX_LIMIT = 200; // UNCOMMENTING THIS WILL CAUSE A COMPILE ERROR
        System.out.println("Note: c.MAX_LIMIT = 200; is commented out because 'final' variables cannot be reassigned.");
    }
}