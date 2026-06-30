package Unit_1;

// 1. Creating thread by extending Thread class
class ThreadClassExample extends Thread {
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("Thread Class Printing: " + i);
            try { Thread.sleep(500); } catch (InterruptedException e) {}
        }
    }
}

// 2. Creating thread by implementing Runnable interface
class RunnableExample implements Runnable {
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("Runnable Printing: " + i);
            try { Thread.sleep(500); } catch (InterruptedException e) {}
        }
    }
}

public class ThreadDemo {
    public static void main(String[] args) {
        System.out.println("--- Multithreading Demo ---");

        // a. Create threads
        ThreadClassExample t1 = new ThreadClassExample();
        Thread t2 = new Thread(new RunnableExample());

        // b. Start threads to print concurrently
        t1.start();
        t2.start();
    }
}
