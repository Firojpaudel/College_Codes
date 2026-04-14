package Unit_1;

class Student {
    String name;
    int marks;

    // Constructor
    Student(String name, int marks) {
        this.name = name;
        this.marks = marks;
    }
}

public class StudentSearch {
    public static void main(String[] args) {
        // a. Store students in an array
        Student[] students = {
                new Student("John", 85),
                new Student("Sita", 92),
                new Student("Ali", 78),
                new Student("Bikash", 95),
                new Student("Maya", 88)
        };

        // b. Find the student with highest marks
        Student topper = students[0];

        for (Student s : students) {
            if (s.marks > topper.marks) {
                topper = s;
            }
        }

        // Display Result
        System.out.println("--- Top Student ---");
        System.out.println("Name: " + topper.name);
        System.out.println("Marks: " + topper.marks);
    }
}