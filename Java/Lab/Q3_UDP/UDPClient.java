import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPClient {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket()) {
            String message = "Hello from UDP client";
            byte[] sendBuffer = message.getBytes();
            InetAddress serverAddress = InetAddress.getByName("localhost");

            DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, 9090);
            socket.send(sendPacket);
            System.out.println("Message sent.");

            byte[] receiveBuffer = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            socket.receive(receivePacket);

            String ack = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Server reply: " + ack);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
