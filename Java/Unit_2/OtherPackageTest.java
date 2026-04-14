package Unit_2;

import Unit_1.BaseClass;

public class OtherPackageTest extends BaseClass {
    public static void main(String[] args) {
        BaseClass obj = new BaseClass();
        OtherPackageTest subObj = new OtherPackageTest();

        System.out.println("--- Access from DIFFERENT PACKAGE ---");
        System.out.println("1. Accessible: " + obj.publicVar);
        
        System.out.println("// 2. NOT Accessible directly: obj.protectedVar");
        System.out.println("3. Accessible via Inheritance (Subclass): " + subObj.protectedVar);

        System.out.println("// 4. NOT Accessible: obj.defaultVar (Compile Error)");
        System.out.println("// 5. NOT Accessible: obj.privateVar (Compile Error)");
    }
}
