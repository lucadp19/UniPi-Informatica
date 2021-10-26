import java.util.concurrent.*;
import java.util.concurrent.ThreadPoolExecutor.AbortPolicy;
/**
 * BoxOffice
 */
public class BoxOffice {
    public static final int numMachines = 5;
    public static final int numVisitors = 50;
    public static final int maxWaitingVisitors = 10;
    public static final long delay = 50L;

    public static class Visitor implements Runnable { 
        private int id;

        public Visitor(int id){
            this.id = id;
        }

        public void run(){
            try {
                int waiting = ThreadLocalRandom.current().nextInt(0, 1001);
                System.out.printf("Visitatore %d: sto acquistando un biglietto.\n", this.id);
                Thread.sleep(waiting);
            } catch(InterruptedException e){
                e.printStackTrace();
            }
            System.out.printf("Visitatore %d: ho acquistato un biglietto.\n", this.id);
        }
    }

    public static void main(String[] args) {
        BlockingQueue<Runnable> queue =  new ArrayBlockingQueue<Runnable>(maxWaitingVisitors);
        ExecutorService pool = new ThreadPoolExecutor(
            numMachines, 
            numMachines, 
            0L, 
            TimeUnit.MILLISECONDS,
            queue,
            new ThreadPoolExecutor.AbortPolicy()
        );

        for(int i = 0; i < numVisitors; i++) {
            try {
                pool.execute(new Visitor(i));
            } catch(RejectedExecutionException e) {
                System.out.printf("Visitatore %d: sala esaurita.\n", i);
            }

            try {
                Thread.sleep(delay);
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
        }
    }    
}