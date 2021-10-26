import java.util.*;
import java.util.concurrent.*;

public class PostOffice {
    public static final int numCounters = 4;            /** Number of counters */
    public static final int terminationDelay = 7000;    /** Delay before shutdownNow */
    public static final int waitBeforeAttempt = 10;     /** Time to wait before trying to enter inner room again */

    public static class Customer implements Runnable, Comparable<Customer> {
        private int id;             /** Customer ID */
        private int minTime = 50;   /** Minimum waiting time at the counter */
        private int maxTime = 5000; /** Maximum waiting time at the counter */

        public Customer(int id){ this.id = id; }
        public int getID() { return this.id; }
        public void run(){
            try {
                System.out.println("Customer no. " + id + " is being served.");
                // waiting at the counter
                int waitingTime = ThreadLocalRandom.current().nextInt(minTime, maxTime+1);
                Thread.sleep(waitingTime);
            } catch(InterruptedException e){
                System.out.println("Customer no. " + id + " was thrown out.");
            }

            System.out.println("Customer no. " + id + " is leaving.");
        }
        // Used to order customers
        public int compareTo(Customer c){
            return this.id - c.getID();
        }
    }
    
    public static void main(String[] args) {
        if(args.length < 1){
            System.err.println("Run this app as: java PostOffice <max capacity of inner room> <num visitors>");
            System.exit(1);
        }

        int maxCapacityInnerRoom = Integer.parseInt(args[0]);
        int numVisitors = Integer.parseInt(args[1]);

        PriorityQueue<Customer> outerRoom = new PriorityQueue<>();
        BlockingQueue<Runnable> innerRoom = new ArrayBlockingQueue<>(maxCapacityInnerRoom);

        ExecutorService pool = new ThreadPoolExecutor(
            numCounters, 
            numCounters, 
            0L, 
            TimeUnit.MILLISECONDS, 
            innerRoom,
            new ThreadPoolExecutor.AbortPolicy()
        );

        // every customer enters the outer room at the beginning
        for(int i = 0; i < numVisitors; i++)
            outerRoom.add(new Customer(i));
        
        try {
            while(!outerRoom.isEmpty()){
                // customer that should enter the inner room
                Customer next = outerRoom.peek();
                try {
                    pool.execute(next);
                    // if no exception is thrown then the highest priority customer has entered the inner room
                    // hence we can remove them from the outer room
                    System.out.println("Customer no. " + next.getID() + " entered inner room.");
                    outerRoom.poll();
                } catch(RejectedExecutionException e) { 
                    // waiting a bit
                    Thread.sleep(waitBeforeAttempt);
                }
            }
        } catch(InterruptedException e) {
            System.out.println("Closing post office.");
        }

        pool.shutdown();
        try {
            if(!pool.awaitTermination(terminationDelay, TimeUnit.MILLISECONDS))
                pool.shutdownNow();
        } catch(InterruptedException e){
            pool.shutdownNow();
        }
    }
}
