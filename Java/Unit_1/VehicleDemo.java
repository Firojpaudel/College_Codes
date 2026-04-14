package Unit_1;

class Vehicle {
    void run() {
        System.out.println("Vehicle is running");
    }
}

// Subclass Car
class Car extends Vehicle {
    @Override
    void run() {
        System.out.println("Car is running safely with 4 wheels");
    }
}

// Subclass Bike
class Bike extends Vehicle {
    @Override
    void run() {
        System.out.println("Bike is running fast with 2 wheels");
    }
}

public class VehicleDemo {
    public static void main(String[] args) {
        System.out.println("--- Question 11: Vehicle Inheritance ---");

        // Dynamic Method Dispatch (Executing the overridden methods)
        Vehicle v1 = new Car();
        Vehicle v2 = new Bike();

        v1.run();
        v2.run();
    }
}
