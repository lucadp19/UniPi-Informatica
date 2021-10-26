import java.util.*;

public class SynchronizedList<T> {
    private LinkedList<T> list;

    SynchronizedList(){ list = new LinkedList<>(); }

    public synchronized void add(T elem){
        list.add(elem);
        this.notifyAll(); // waking up threads blocked on removeFirst
    }

    public synchronized T removeFirst() throws InterruptedException {
        while(list.isEmpty()) this.wait(); // waiting for an element to be inserted into this

        return list.removeFirst();
    }
}
