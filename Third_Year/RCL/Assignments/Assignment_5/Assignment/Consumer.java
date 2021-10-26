import java.io.*;
import java.util.concurrent.*;

public class Consumer implements Runnable {
    private SynchronizedList<File> dirs; /** syncrhonized list to communicate with producer */

    public Consumer(SynchronizedList<File> dirs) { this.dirs = dirs; }

    public void run() {
        File dir = null;

        try{ 
            while(true){
                dir = dirs.removeFirst(); // waits for a directory to be inserted into dirs
                
                if(dir.getName().isEmpty()) return; // job terminated
                
                System.out.printf("Thread %d: got directory %s!\n", Thread.currentThread().getId(), dir.getName());

                // printing all files in directory
                File[] files = dir.listFiles();
                for(File file : files)
                    System.out.printf("Thread %d: read file %s.\n", Thread.currentThread().getId(), file.getName());
            }
        } catch(InterruptedException ex) {
            System.out.println("Thread " + Thread.currentThread().getId() + " interrupted :(");
        }
    }
}
