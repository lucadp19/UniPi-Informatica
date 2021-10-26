import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Assignment {
    private final static int numWriters = 20;
    private final static int numReaders = 20;
    private final static long awaitTermTimeout = 2000;

    public static void main(String[] args) {
        Counter counter = new Counter();
        ExecutorService pool = Executors.newCachedThreadPool();
        long estimatedTime;
        
        // first test: no locks
        System.out.println("Starting first test: counter without locks.");
        estimatedTime = Assignment.test(counter, pool);
        System.out.printf("First test completed. Estimated time: %d milliseconds.\n", estimatedTime);

        // second test: reentrant locks
        counter = new CounterLock();
        pool = Executors.newCachedThreadPool();
        System.out.println("Starting second test: counter with reentrant locks.");
        estimatedTime = Assignment.test(counter, pool);
        System.out.printf("Second second completed. Estimated time: %d milliseconds.\n", estimatedTime);

        // third test: read-write locks
        counter = new CounterRWLock();
        pool = Executors.newCachedThreadPool();
        System.out.println("Starting third test: counter with read-write locks.");
        estimatedTime = Assignment.test(counter, pool);
        System.out.printf("Third second completed. Estimated time: %d milliseconds.\n", estimatedTime);
    }

    /**
     * Tests the counter class (and its locks) and returns the estimated time.
     */
    public static long test(Counter counter, ExecutorService pool){
        long startTime = System.currentTimeMillis();

        for(int i = 0; i < numWriters; i++)
            pool.execute(new Writer(counter));
        for(int i = 0; i < numReaders; i++)
            pool.execute(new Reader(counter));

        pool.shutdown();
        try {
            if(!pool.awaitTermination(awaitTermTimeout, TimeUnit.MILLISECONDS))
                pool.shutdownNow();
        } catch(InterruptedException e) {
            System.out.println("Process interrupted!");
            System.exit(1);
        }
        long endTime = System.currentTimeMillis();

        return endTime - startTime;
    }
}