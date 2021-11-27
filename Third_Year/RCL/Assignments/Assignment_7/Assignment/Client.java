import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Client {
    /**
     * Class for measuring PING stats
     */
    private static class PingStatistics {
        public long max = Long.MIN_VALUE;   /** max RTT */
        public long min = Long.MAX_VALUE;   /** min RTT */
        public long noPackets;              /** number of sent packets */
        public long recvPackets = 0;        /** number of received packets */
        public long lostPackets = 0;        /** number of lost packets */
        public long packetLoss;             /** packet loss percentage */
        public double avg = 0;              /** average RTT */

        public PingStatistics(List<Optional<Long>> RTTs){
            noPackets = RTTs.size();

            for(Optional<Long> deltaTime : RTTs){
                if(deltaTime.isPresent()){
                    if(deltaTime.get() > max) max = deltaTime.get();
                    if(deltaTime.get() < min) min = deltaTime.get();
                    avg += deltaTime.get();
                } else {
                    lostPackets++;
                }
            }

            recvPackets = noPackets - lostPackets;
            avg = avg / recvPackets;
            packetLoss = (lostPackets * 100) / noPackets;
        }

        public void printStats(){
            System.out.println("\n--- PING Statistics ---");
            System.out.printf(
                "%d packets transmitted, %d received, %d%% packet loss\n", 
                noPackets, recvPackets, packetLoss
            );
            System.out.printf(
                "round-trip (ms) min/avg/max %d/%.2f/%d\n", 
                min, avg, max
            );
        }
    }

    final static String usageStr = "Usage: java Client <address> <port>";
    final static int timeout    = 2000;
    final static int respSize   = 1024;
    final static int noPackets  = 10;

    public static void main(String[] args) {
        if(args.length != 2){
            System.err.println("ERR -arg 1 -arg 2");
            System.exit(1);
            // System.err.println(usageStr);
        }

        // parsing port
        int serverPort = 0;
        try { serverPort = Integer.parseInt(args[1]); }
        catch(NumberFormatException ex){
            System.err.println("ERR -arg 2");
            // System.err.println(usageStr);
            System.exit(1);
        } 
        
        // parsing address
        String address = args[0];
        InetAddress serverAddr = null;
        try { serverAddr = InetAddress.getByName(address); }
        catch (UnknownHostException ex){
            System.err.println("ERR -arg 1");
            // System.err.println(usageStr);
            System.exit(1);
        }

        // list of RTTs
        // the Optional is used to model lost packets
        List<Optional<Long>> RTTs = new ArrayList<>(10);

        for(int i = 0; i < noPackets; i++){
            try (
                DatagramSocket clientSock = new DatagramSocket(0);
            ){
                clientSock.setSoTimeout(timeout);
                final long startTime = System.currentTimeMillis();
                final String msg = "PING " + i + " " + startTime;
                byte[] buf = (msg + "\n").getBytes();

                DatagramPacket packet = new DatagramPacket(
                    buf, buf.length, serverAddr, serverPort 
                );

                // sending request to server
                try { clientSock.send(packet); }
                catch (IOException ex) {
                    System.err.println("IO Error while sending packet no. " + i + ".");
                    ex.printStackTrace();
                    System.err.println("Aborting.");
                    System.exit(1);
                }

                // getting response from server
                DatagramPacket response = new DatagramPacket(new byte[respSize], respSize);
                try { clientSock.receive(response); } 
                catch (SocketTimeoutException ex) { // response was not received in time
                    RTTs.add(Optional.empty());
                    System.out.println(msg + " -- RTT: *");
                    continue;
                } catch (IOException ex) {
                    System.err.println("IO Error while receiving response no. " + i + ".");
                    ex.printStackTrace();
                    System.err.println("Aborting.");
                    System.exit(1);
                }

                // no catch => response was received in time
                Long currElapsed = System.currentTimeMillis() - startTime;
                RTTs.add(Optional.of(currElapsed));
                System.out.println(msg + " -- RTT: " + currElapsed + " ms");
            } catch (SocketException ex){
                System.err.println("SocketException while sending/receiving packet no. " + i + ".");
                ex.printStackTrace();
                System.err.println("Aborting.");
                System.exit(1);
            }
        }

        // getting statistics
        PingStatistics stats = new PingStatistics(RTTs);
        stats.printStats();
    }
}