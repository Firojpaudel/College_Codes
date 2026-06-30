package Unit_1;

public class BaseClass {
    public String publicVar = "Public Variable";
    protected String protectedVar = "Protected Variable";
    String defaultVar = "Default (Package-Private) Variable";
    private String privateVar = "Private Variable";

    public void display() {
        System.out.println("Access within the SAME CLASS:");
        System.out.println("1. " + publicVar);
        System.out.println("2. " + protectedVar);
        System.out.println("3. " + defaultVar);
        System.out.println("4. " + privateVar);
    }
}
