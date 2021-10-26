import java.util.*;
import java.io.*;

/**
 * Main
 */
public class Main {
    public static LinkedList<File> dirs = new LinkedList<>();
    public static String outfiles = "/tmp/files";
    public static String outdirs  = "/tmp/dirs"; 

    public static void main(String[] args) {
        if(args.length != 1) {
            System.err.println("ERROR: there should be exactly one additional argument, the path to the root directory to recursively enumerate.");
            System.exit(1);
        }

        File rootDir = new File(args[0]);
        if(!rootDir.isDirectory()){
            System.err.println("ERROR: the additional argument must be the path to the root directory to recursively enumerate.");
            System.exit(1);
        }

        FileOutputStream outstrFiles = null, outstrDirs = null;
        try {
            outstrFiles = new FileOutputStream(outfiles);
            outstrDirs  = new FileOutputStream(outdirs);
        } catch(Exception ex){
            System.err.println("ERROR: couldn't open " + outfiles + " or " + outdirs + ".");
            System.exit(1);
        }

        dirs.add(rootDir);
        try{
            while(!dirs.isEmpty()){
                File[] files = dirs.removeFirst().listFiles();
                for(File file: files){
                    String filename = file.getName() + "\n";
                    
                    if(file.isDirectory()){
                        dirs.add(file);
                        outstrDirs.write(filename.getBytes());
                    } else {
                        outstrFiles.write(filename.getBytes());
                    }
                }
            }
        } catch(IOException ex){
            ex.printStackTrace();
            System.exit(1);
        }

        try {
            outstrDirs.close();
            outstrFiles.close();
        } catch(IOException ex){
            ex.printStackTrace();
            System.exit(1);
        }

    }
}