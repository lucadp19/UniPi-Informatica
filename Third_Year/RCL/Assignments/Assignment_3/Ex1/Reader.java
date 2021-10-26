public class Reader implements Runnable {
    private Counter counter;

    public Reader(Counter counter){ this.counter = counter; }
    public void run(){
        int val = counter.get();
        System.out.printf("[R] Thread %d: counter's value is %d.\n", Thread.currentThread().getId(), val);
    }
}
