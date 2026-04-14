package Unit_1;

// Define an interface
interface Shape {
    double getArea(); // Abstract method
}

// Implement the interface in Circle
class Circle implements Shape {
    double radius;

    Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return Math.PI * radius * radius;
    }
}

// Implement the interface in Rectangle
class Rectangle implements Shape {
    double length, width;

    Rectangle(double l, double w) {
        this.length = l;
        this.width = w;
    }

    @Override
    public double getArea() {
        return length * width;
    }
}

public class InterfaceDemo {
    public static void main(String[] args) {
        // dynamic method dispatch (Polymorphism)
        Shape s1 = new Circle(5);
        Shape s2 = new Rectangle(10, 5);

        System.out.println("--- Dynamic Area Calculation ---");
        System.out.printf("Area of Circle (radius 5): %.2f\n", s1.getArea());
        System.out.printf("Area of Rectangle (10x5): %.2f\n", s2.getArea());
    }
}