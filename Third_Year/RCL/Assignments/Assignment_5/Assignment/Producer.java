import java.io.*;
import java.util.*;

public class Producer implements Runnable {
    private SynchronizedList<File> dirs;    /** synchronized list with consumers */
    private LinkedList<File> privateDirs;   /** private list for recursing directories */
    private File rootDir;                   /** starting directory */

    public Producer(SynchronizedList<File> dirs, String rootDirPath) throws FileNotFoundException {
        this.dirs = dirs;
        this.rootDir = new File(rootDirPath);
        this.privateDirs = new LinkedList<>();

        // checks that the given path actually corresponds to a directory
        if(!rootDir.isDirectory()) throw new FileNotFoundException(rootDir.getName() + " is not a directory");
    }

    public void run() {
        // adding root to both lists
        dirs.add(rootDir); privateDirs.add(rootDir);

        // recursing on private list
        while(!privateDirs.isEmpty()){
            File[] subfiles = privateDirs.removeFirst().listFiles();

            // adding subdirectories to both lists
            for(File subfile : subfiles)
                if(subfile.isDirectory()) {
                    dirs.add(subfile); privateDirs.add(subfile);
                }
        }
    }
}
