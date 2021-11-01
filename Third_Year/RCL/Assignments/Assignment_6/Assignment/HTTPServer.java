import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class HTTPServer {
    private static final int defaultPort = 6789;
    private static final String GET         = "GET";
    private static final String CONT_TYPE   = "Content-Type: ";
    private static final String CONT_LEN    = "Content-Length: ";
    private static final String CONN_CLOSE  = "Connection: close";

    private int port;

    public HTTPServer(int port){ this.port = port; }
    public HTTPServer(){ this(defaultPort); }

    private static String getContentType(final String filename){
        return switch (filename.substring(filename.length() - 3)) {
            case "jpg" -> "image/jpeg";
            case "png" -> "image/png";
            case "mp3" -> "audio/mp3";
            case "mp4" -> "video/mp4";
            case "txt" -> "text/plain";
            default    -> "text/html";
        };
    } 

    public void runServer(){
        try(ServerSocket sock = new ServerSocket(port)){
            while(true){
                System.out.println("Waiting for connection...");
                try(
                    Socket conn = sock.accept();
                    BufferedOutputStream out = new BufferedOutputStream(conn.getOutputStream());
                    BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
                ){
                    System.out.println("Connection accepted!");
                    final String clientRequest = in.readLine();
                    final String[] requestSections = clientRequest.split(" ");
                    if(requestSections.length != 3){
                        System.err.println("Badly formatted message :(");
                        System.err.println("\tRequest message: " + clientRequest);
                        continue;
                    }
                    final String filepath = requestSections[1];
                    final String httpVersion = requestSections[2];
                    if(!requestSections[0].equals(GET)){ // request isn't a GET request
                        System.err.println("Not a HTTP GET request :(");
                        byte[] msg = "Request is not a HTTP GET request".getBytes();
                        sendGETResponse(out, msg, httpVersion, "501 Not Implemented", "text/plain");
                        continue;
                    }

                    // request is a GET request
                    File file = new File(filepath);
                    String contentType = getContentType(filepath);
                    if(!file.exists()){ // file doesn't exist
                        System.err.println("File doesn't exist :(");
                        byte[] msg = "Requested file does not exist".getBytes();
                        sendGETResponse(out, msg, httpVersion, "404 Not Found", "text/plain");
                        continue;
                    }
                    if(!file.isFile()){ // is not a regular file
                        System.err.println("File is not a regular file :(");
                        byte[] msg = "Requested file is not a regular file".getBytes();
                        sendGETResponse(out, msg, httpVersion, "406 Not Acceptable", "text/plain");
                        continue;
                    }
                    
                    // file can be correctly sent
                    try(
                        BufferedInputStream fileIn = new BufferedInputStream(new FileInputStream(file))
                    ){
                        byte[] contents = fileIn.readAllBytes();
                        sendGETResponse(out, contents, httpVersion, "200 OK", contentType);
                        System.out.println("File sent! Closing connection.");
                    }                  
                }
            }
        } catch(IOException ex){ }
    }

    private static void sendGETResponse(
                BufferedOutputStream out, 
                byte[] contents, 
                String httpVersion,
                String httpCode,
                String contentType
            ) throws IOException {
        out.write((httpVersion + " " + httpCode + "\n").getBytes());
        out.write((CONT_LEN + contents.length + "\n").getBytes());
        out.write((CONT_TYPE + contentType + "\n").getBytes());
        out.write((CONN_CLOSE + "\n\n").getBytes());
        out.write(contents);
        out.write("\n".getBytes());
        out.flush();
    }

    public static void main(String[] args) {
        HTTPServer server = new HTTPServer();
        server.runServer();
    }
}
