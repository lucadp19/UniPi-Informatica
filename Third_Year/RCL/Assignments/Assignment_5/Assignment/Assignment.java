import java.util.*;
import java.io.*;
import java.util.concurrent.*;

public class Assignment {
    private static final int noConsumers = 20;
    private static final long terminationDelay = 5000;

    public static void main(String[] args) {
        if(args.length != 1){
            System.err.println("There should be exactly one additional argument: the path to the root directory.");
            System.exit(1);
        }

        SynchronizedList<File> dirs = new SynchronizedList<>();
        Thread prodThread = null;

        // creating producer thread
        try { 
            prodThread = new Thread(new Producer(dirs, args[0]));
        }
        catch(FileNotFoundException ex){ // args[0] was not a directory
            ex.printStackTrace(); System.exit(1); 
        }
        prodThread.start();

        // starting consumer threads
        ExecutorService pool = Executors.newFixedThreadPool(noConsumers);
        for(int i = 0; i < noConsumers; i++)
            pool.execute(new Consumer(dirs));
        
        // waiting for producer thread to terminate
        try { prodThread.join(); }
        catch(InterruptedException ex){ }

        // sending empty file to consumer to stop them
        for(int i = 0; i < noConsumers; i++)
            dirs.add(new File(""));

        pool.shutdown();
        try {
            if(!pool.awaitTermination(terminationDelay, TimeUnit.MILLISECONDS))
                pool.shutdownNow();
        } catch(InterruptedException e){
            pool.shutdownNow();
        }
    }   
}