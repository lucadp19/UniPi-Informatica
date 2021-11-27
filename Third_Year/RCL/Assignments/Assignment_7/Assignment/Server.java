import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Random;

public class Server {
    private final static String usageStr = "Usage: java Server <port> [<seed>]";
    private final static double missPercentage = 0.25;
    private final static int bufSize = 1024;
    private final static int minPing = 5;
    private final static int maxPing = 300;

    public static void main(String[] args) {
        if(args.length != 1 && args.length != 2){ // checking arg number
            System.err.println("Ping Server error: wrong argument number");
            System.err.println(usageStr);
            System.exit(1);
        }

        // parsing port
        int port = -1;
        try { port = Integer.parseInt(args[0]); }
        catch (NumberFormatException ex) {
            System.err.println("ERR -arg 1");
            // System.err.println(usageStr);
            System.exit(1);
        } 

        // parsing seed (if present)
        long seed = System.currentTimeMillis();
        if(args.length == 2){
            try { seed = Integer.parseInt(args[1]); }
            catch (NumberFormatException ex) {
                System.err.println("ERR -arg 2");
                // System.err.println(usageStr);
                System.exit(1);
            }
        }
        Random random = new Random(seed);

        try (DatagramSocket serverSock = new DatagramSocket(port); ){
            while(true){
                // receiving new packet
                DatagramPacket request = new DatagramPacket(new byte[bufSize], bufSize);
                try { serverSock.receive(request); }
                catch (IOException ex){
                    System.err.println("IO Exception caught");
                    ex.printStackTrace();
                    System.err.println("Aborting.");
                    System.exit(1);
                }

                // check if lost
                boolean isLost = random.nextDouble() < missPercentage;
                if(isLost) { System.out.println("PING lost."); continue; } 

                // simulating waiting time
                int ping = random.nextInt(maxPing - minPing) + minPing;
                Thread.sleep(ping);
                
                // sending response
                byte[] buffer = request.getData();
                InetAddress clientAddr = request.getAddress(); 
                int clientPort = request.getPort();
                DatagramPacket response = new DatagramPacket(
                    buffer, buffer.length, clientAddr, clientPort
                );

                try { serverSock.send(response); }
                catch (IOException ex){
                    System.err.println("IO Exception caught");
                    ex.printStackTrace();
                    System.err.println("Aborting.");
                    System.exit(1);
                }

                // printing stats
                System.out.printf(
                    "PING sent after %d ms to client with \n\tIP Address: %s\n\tPort: %d\n",
                    ping, clientAddr.getHostAddress(), clientPort
                );
            }
        } catch (SocketException ex){
            System.err.println("SocketException caught");
            ex.printStackTrace();
            System.err.println("Aborting.");
            System.exit(1);
        } catch (InterruptedException ex) {
            System.out.println("Server interrupted");
            System.exit(0);
        }
    }
}