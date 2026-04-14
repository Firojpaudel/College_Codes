package Unit_1;

// a. Create a custom exception class
class InsufficientBalanceException extends Exception {
    public InsufficientBalanceException(String message) {
        super(message);
    }
}

public class CustomExceptionDemo {
    public static void main(String[] args) {
        double balance = 5000.00;
        double withdrawal = 6000.00; // More than balance

        System.out.println("--- Bank Account Demo ---");
        System.out.println("Current Balance: " + balance);
        System.out.println("Attempting withdrawal of: " + withdrawal);

        try {
            // b. Throw custom exception if withdrawal exceeds balance
            if (withdrawal > balance) {
                throw new InsufficientBalanceException("Error: You don't have enough money!");
            }
            balance -= withdrawal;
            System.out.println("Withdrawal successful! New balance: " + balance);
        } catch (InsufficientBalanceException e) {
            // Handle the custom exception
            System.err.println("Transaction Failed: " + e.getMessage());
        }

        System.out.println("\nThank you for using our bank.");
    }
}
