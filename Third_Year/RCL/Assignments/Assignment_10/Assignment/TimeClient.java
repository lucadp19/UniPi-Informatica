import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;

public class TimeClient {
    private final static int noPackets = 10;
    private final static int timeout = 5000;
    private final static int bufLen = 1024;
    private final static String usage = 
        "Usage: java TimeClient <multicast addr> <port>\n" + 
        "The multicast address must begin with 0xFF, i.e. multicast addresses are from \"224.0.0.0\" to \"239.255.255.255\"!";

    public static void main(String[] args) {
        if(args.length != 2){
            System.err.println("ERROR: there should be 2 additional arguments.");
            System.err.println(usage);
            System.exit(1);
        }

        InetAddress addr = null;
        int port = -1;
        
        // getting the address
        try { addr = InetAddress.getByName(args[0]); }
        catch(UnknownHostException ex) {
            System.err.println("ERROR: \"" + args[0] + "\" is not a valid host.");
            System.err.println(usage);
            System.err.println("Aborting.");
            System.exit(1);
        }
        // getting the port number
        try { port = Integer.parseInt(args[1]); }
        catch(NumberFormatException ex) {
            System.err.println("ERROR: \"" + args[0] + "\" is not a valid port.");
            System.err.println(usage);
            System.err.println("Aborting.");
            System.exit(1);
        }

        try ( MulticastSocket sock = new MulticastSocket(port); ) { 
            sock.joinGroup(addr); // joining the multicast group
            sock.setSoTimeout(timeout);
            
            for(int i = 0; i < noPackets; i++){
                byte[] buf = new byte[bufLen];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                
                try { sock.receive(packet); }
                catch(SocketTimeoutException ex){
                    System.err.println("Packet took too long. Aborting.");
                    System.exit(1);
                }
                // writing to stdout the msg received
                System.out.printf(
                    "Read number %2d:\t time is \"%s\".\n", 
                    i + 1, 
                    new String(packet.getData(), StandardCharsets.UTF_8)
                );
            }
            sock.leaveGroup(addr); // leaving the group
        } catch(IOException ex) {
            ex.printStackTrace();
            System.err.println(usage);
            System.exit(1); 
        }
    }    
}