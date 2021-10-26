public class Writer implements Runnable{
    private Counter counter;

    public Writer(Counter counter){ this.counter = counter; }
    public void run(){
        counter.increment();
        System.out.printf("[W] Thread %d: incremented counter's value by one.\n", Thread.currentThread().getId());
    }
}
