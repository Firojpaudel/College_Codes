package Unit_1;

class Athlete {
    void run() {
        System.out.println("Athlete is running...");
    }
}

class Sprinter extends Athlete {
    @Override
    void run() {
        System.out.println("Sprinter is running 100m at top speed!");
    }
}

class MarathonRunner extends Athlete {
    @Override
    void run() {
        System.out.println("Marathon runner is running 42km with high endurance.");
    }
}

public class InheritanceDemo {
    public static void main(String[] args) {
        Athlete a1 = new Athlete();
        Athlete a2 = new Sprinter();
        Athlete a3 = new MarathonRunner();

        System.out.println("--- Athlete Overriding Demo ---");
        a1.run();
        a2.run();
        a3.run();
    }
}