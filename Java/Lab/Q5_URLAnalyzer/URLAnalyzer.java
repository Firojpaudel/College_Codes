import java.net.URL;
import java.util.Scanner;

public class URLAnalyzer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter URL: ");
        String urlString = scanner.nextLine();

        try {
            URL url = new URL(urlString);
            System.out.println("Protocol: " + url.getProtocol());
            System.out.println("Host Name: " + url.getHost());
            System.out.println("Port: " + (url.getPort() == -1 ? url.getDefaultPort() : url.getPort()));
            System.out.println("File Name: " + url.getFile());
            System.out.println("Query String: " + url.getQuery());
        } catch (Exception e) {
            System.out.println("Invalid URL: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
