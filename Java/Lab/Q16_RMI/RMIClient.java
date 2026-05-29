import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class RMIClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            Calculator calculator = (Calculator) registry.lookup("CalculatorService");

            int a = 10, b = 2;
            System.out.println("Add: " + calculator.add(a, b));
            System.out.println("Subtract: " + calculator.subtract(a, b));
            System.out.println("Multiply: " + calculator.multiply(a, b));
            System.out.println("Divide: " + calculator.divide(a, b));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
