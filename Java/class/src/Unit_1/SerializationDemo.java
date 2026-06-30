package Unit_1;

import java.io.*;

class SerializedStudent implements Serializable {
    private static final long serialVersionUID = 1L;

    int id;
    String name;
    double marks;

    SerializedStudent(int id, String name, double marks) {
        this.id = id;
        this.name = name;
        this.marks = marks;
    }
    @Override
    public String toString() {
        return "Student[ID=" + id + ", Name=" + name + ", Marks=" + marks + "]";
    }
}
public class SerializationDemo {
    public static void main(String[] args) {
        String filename = "student_data.ser";
        SerializedStudent s1 = new SerializedStudent(101, "Firoj Paudel", 92.5);

        System.out.println("--- Serialization Demo ---");

        // a. Serialize the Student object to a file
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(filename))) {
            out.writeObject(s1);
            System.out.println("Object has been serialized to " + filename);
        } catch (IOException e) {
            System.err.println("Serialization Error: " + e.getMessage());
        }

        // b. Deserialize and display the object
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(filename))) {
            SerializedStudent s2 = (SerializedStudent) in.readObject();
            System.out.println("\nObject has been deserialized from " + filename + ":");
            System.out.println(s2);
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Deserialization Error: " + e.getMessage());
        }
    }
}