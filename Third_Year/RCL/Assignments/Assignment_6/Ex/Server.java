import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static int defaultPort = 6789;
    public static String defaultFile = "./test.txt";
    private int port;
    private String file;
    
    public Server(int port, String file){
        this.port = port;
        this.file = file;
    }
    public Server(){
        this(Server.defaultPort, Server.defaultFile);
    }

    public void runServer(){
        try(ServerSocket sock = new ServerSocket(port)){
            while(true){
                try(
                    Socket conn = sock.accept();
                    BufferedOutputStream out = new BufferedOutputStream(conn.getOutputStream());
                    BufferedInputStream fileIn = new BufferedInputStream(new FileInputStream(file));
                ){
                    int bufferSize = 256;
                    byte[] byteBuffer = new byte[bufferSize];
                    int numberOfBytes;
                    do {
                        numberOfBytes = fileIn.read(byteBuffer, 0, bufferSize);
                        if(numberOfBytes >= 0) out.write(byteBuffer, 0, numberOfBytes);
                    } while (numberOfBytes >= 0);
                }
            }
        } catch(IOException ex){ }
    }

    public static void main(String[] args) {
        Server server = new Server();
        server.runServer();
    }
}
