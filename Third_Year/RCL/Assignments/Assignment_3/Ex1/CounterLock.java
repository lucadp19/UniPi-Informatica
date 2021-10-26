import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CounterLock extends Counter {
    private Lock lock;

    public CounterLock(){
        super();
        lock = new ReentrantLock();
    }
    public CounterLock(int initValue){
        super(initValue);
        lock = new ReentrantLock();
    }

    public int get(){
        lock.lock();
        int val = super.get();
        lock.unlock();

        return val;
    }

    public void increment() {
        lock.lock();
        super.increment();
        lock.unlock();
    }
}