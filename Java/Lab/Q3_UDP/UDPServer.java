import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPServer {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket(9090)) {
            byte[] receiveBuffer = new byte[1024];
            System.out.println("UDP Server waiting for messages...");

            DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            socket.receive(receivePacket);

            String message = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Client says: " + message);

            InetAddress clientAddress = receivePacket.getAddress();
            int clientPort = receivePacket.getPort();
            String ackMessage = "Acknowledgment: Message received";
            byte[] sendBuffer = ackMessage.getBytes();

            DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, clientAddress, clientPort);
            socket.send(sendPacket);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
