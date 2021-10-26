import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class CounterRWLock extends Counter {
    private ReadWriteLock lock;
    private Lock readLock;
    private Lock writeLock;

    public CounterRWLock(){
        initLocks();
    }
    public CounterRWLock(int initValue){
        super(initValue);
        initLocks();
    }

    private void initLocks(){
        lock = new ReentrantReadWriteLock();
        readLock = lock.readLock();
        writeLock = lock.writeLock();
    }

    public int get(){
        readLock.lock();
        int val = super.get();
        readLock.unlock();

        return val;
    }

    public void increment() {
        writeLock.lock();
        super.increment();
        writeLock.unlock();
    }
}