package Unit_1;

public class SamePackageTest {
    public static void main(String[] args) {
        BaseClass obj = new BaseClass();

        System.out.println("--- Access from SAME PACKAGE ---");
        System.out.println("1. Accessible: " + obj.publicVar);
        System.out.println("2. Accessible: " + obj.protectedVar);
        System.out.println("3. Accessible: " + obj.defaultVar);
        System.out.println("// 4. NOT Accessible: obj.privateVar (Compile Error)");
    }
}