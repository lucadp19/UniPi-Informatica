import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;

public class Server {
    public final static int bufSize = 1024;
    public final static int port = 6789;

    public static void main(String[] args) {
        byte pong[] = new String("PONG").getBytes();
        byte buf[] = new byte[bufSize];
        try (
            DatagramSocket socket = new DatagramSocket(port);
        ){
            DatagramPacket request = new DatagramPacket(buf, buf.length);
            socket.receive(request);
            System.out.println("Received " + new String(request.getData()) + ".");

            InetAddress clientAddr = request.getAddress();
            int clientPort = request.getPort();
            DatagramPacket response = new DatagramPacket(
                pong, pong.length, clientAddr, clientPort
            );
            socket.send(response);
            System.out.println("Sent PONG.");
        } catch(Exception ex){
            System.err.println("An error occurred, but we don't know which.");
        }
    }
}
