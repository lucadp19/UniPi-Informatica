import java.util.concurrent.*; 

/**
 * Main
 */
public class Main {
    private static int maxDelay = 500;

    public static class Dropbox {
        private int buf;
        private boolean isEmpty;

        public Dropbox(){
            buf = 0;
            isEmpty = true;
        }
        public Dropbox(int init){
            buf = init;
            isEmpty = false;
        }

        public synchronized int take() throws InterruptedException {
            // wait until the buffer has an element
            while(isEmpty)
                this.wait();
            
            isEmpty = true;
            this.notifyAll(); // now buffer is empty
            return buf;
        }

        public synchronized void put(int val) throws InterruptedException {
            // wait until the buffer is empty
            while(!isEmpty)
                this.wait();
            
            isEmpty = false;
            buf = val;
        }
    }

    public static class Consumer implements Runnable {
        private boolean takeEven;
        private Dropbox db;

        public Consumer(boolean takeEven, Dropbox db){
            this.takeEven = takeEven;
            this.db = db;
        }

        public void run(){
            try {
                System.out.println("Consumer " + Thread.currentThread().getId() + ": trying to take an " + (takeEven ? "even" : "odd") + " value.");
                int val;
                while(true){
                    val = db.take();
                    if((val % 2 == 0) == takeEven)
                        break;
                }
                System.out.printf("Consumer %d: took %d.\n", Thread.currentThread().getId(), val);
            } catch(InterruptedException e) { System.out.printf("Consumer %d interrupted.\n", Thread.currentThread().getId()); }
        }
    }

    public static class Producer implements Runnable {
        private Dropbox db;
        
        public Producer(Dropbox db){ this.db = db; }

        public void run(){
            try {
                int val = ThreadLocalRandom.current().nextInt(0, 100);
                db.put(val);
                System.out.printf("Producer %d: produced value %d.\n", Thread.currentThread().getId(), val);
            } catch(InterruptedException e) {
                System.out.println("Producer interrupted.");
            }
        }
    }

    public static void main(String[] args) {
        Dropbox db      = new Dropbox();
        Thread consEven = new Thread(new Consumer(true, db)),
            consOdd     = new Thread(new Consumer(false, db)),
            prod        = new Thread(new Producer(db));

        consEven.start(); consOdd.start(); prod.start();
        try {
			// Attendo `maxDelay` millisecondi e poi forzo
			// la terminazione di tutti i thread.
			consEven.join(maxDelay);
            consOdd.join(maxDelay);
            prod.join(maxDelay);
			if (consEven.isAlive()) consEven.interrupt();
			if (consOdd.isAlive())  consOdd.interrupt();
			if (prod.isAlive())     prod.interrupt();
		}
		catch (InterruptedException e) {
			System.err.println("Main: interrupted during join");
			System.exit(1);
		}
    }
}