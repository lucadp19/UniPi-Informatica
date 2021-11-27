import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;

public class Client {
    public final static int bufSize = 1024;
    public final static int timeout = 5000;
    public final static String hostname = "localhost";
    public final static int port = 6789;

    public static void main(String[] args) {
        byte ping[] = new String("PING").getBytes();
        byte buf[] = new byte[bufSize];
        try (
            DatagramSocket socket = new DatagramSocket(0);
        ) {
            socket.setSoTimeout(timeout);

            InetAddress host = InetAddress.getByName(hostname);
            DatagramPacket packet = new DatagramPacket(
                ping, ping.length, host, port
            );
            socket.send(packet);
            System.out.println("Sent PING!");

            DatagramPacket response = new DatagramPacket(buf, buf.length);
            socket.receive(response);
            System.out.println("Received " + new String(response.getData()) + "!");
        } catch(SocketTimeoutException ex){
            System.err.println("No answer received from server :(");
        } catch(Exception e) {
            System.err.println("Some error occurred, but we're not sure which. :(");
        }
    }
}