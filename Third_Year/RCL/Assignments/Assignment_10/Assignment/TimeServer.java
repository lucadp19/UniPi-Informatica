import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;
import java.text.NumberFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class TimeServer {
    private final static long waitingTime = 1000;
    private final static String usage = 
        "Usage: java TimeServer <multicast addr> <port>\n" + 
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

        while(true){
            try ( DatagramSocket socket = new DatagramSocket(); ){
                // creating the new time string
                String date = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss").format(LocalDateTime.now());
                byte[] dateInBytes = date.getBytes(StandardCharsets.UTF_8);
                
                DatagramPacket packet = new DatagramPacket(dateInBytes, dateInBytes.length, addr, port);
                try { socket.send(packet); }
                catch(IOException ex){
                    ex.printStackTrace();
                    System.err.println(usage);
                    System.exit(1);
                }

                // waiting for the next iteration
                try { Thread.sleep(waitingTime); }
                catch(InterruptedException ex){ 
                    ex.printStackTrace();
                    System.exit(1);
                }
            } catch (SocketException ex){
                ex.printStackTrace();
                System.err.println(usage);
                System.exit(1);
            }
        }       
    }
}