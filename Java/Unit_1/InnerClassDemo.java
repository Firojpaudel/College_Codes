package Unit_1;

class Company {
    String companyName = "WiseYak";

    // Inner class definition
    class Employee {
        String empName;

        Employee(String name) {
            this.empName = name;
        }

        void showDetails() {
            // Accessing 'companyName' from the outer class Company
            System.out.println("Employee: " + empName);
            System.out.println("Working at: " + companyName);
        }
    }
}

public class InnerClassDemo {
    public static void main(String[] args) {
        // 1. Create instance of Outer class
        Company myComp = new Company();

        // 2. Create instance of Inner class using Outer class object
        Company.Employee emp = myComp.new Employee("Firoj");

        System.out.println("--- Inner Class Access Demo ---");
        emp.showDetails();
    }
}