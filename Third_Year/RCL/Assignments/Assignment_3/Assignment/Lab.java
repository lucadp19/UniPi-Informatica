import java.util.*;
import java.util.concurrent.locks.*;

public class Lab {
    private static final int defaultNumPC = 20;

    private int numPC;                      /** number of pcs in the lab */
    private Lock generalLock;               /** lock to handle the entrance */
    private ReadWriteLock labLock;          /** locks the lab (writer for the profs, reader for others) */
    private Condition allLocked;            /** condition variable to wait when all pcs are locked */
    private List<Boolean> isPCFree;         /** keeps track of which pcs are free*/

    public Lab(){ this(Lab.defaultNumPC); }
    public Lab(int numPC){ 
        this.numPC = numPC; 

        generalLock = new ReentrantLock();
        allLocked = generalLock.newCondition();
        isPCFree = new ArrayList<Boolean>(numPC);
        labLock = new ReentrantReadWriteLock();

        for(int i = 0; i < numPC; i++) {
            isPCFree.add(true); // all pcs are free at the start
        }
    }

    /** Locks the entire lab. Used by professors. */
    public void lockEntireLab(){ 
        try {
            generalLock.lock();
            while(!allPCsFree()) // checks if all pcs are free
                allLocked.awaitUninterruptibly(); // as soon as one is freed, this thread reawakens
            
            labLock.writeLock().lock();
        } finally { generalLock.unlock(); }
    }

    /** Unlocks the lab after a lockEntireLab. */
    public void unlockEntireLab(){ 
        labLock.writeLock().unlock(); 
    }

    /** Locks a non-specified pc in reader mode. Used by students. */
    public int singlePCLock() {
        int pos;

        try {
            generalLock.lock(); // trying to get in
            while((pos = getFreePosition()) == -1) // no pc are free
                allLocked.awaitUninterruptibly(); // as soon as one is free, this thread reawakens
            isPCFree.set(pos, false);

            labLock.readLock().lock(); // locking to block access from professors
        } finally { generalLock.unlock(); }

        return pos; // returns the occupied pc
    }

    /** Locks a specific pc. Used by thesis students. */
    public void singlePCLock(int pos) {
        try {
            generalLock.lock(); // trying to get in
            while(!isFree(pos)) { // the pos pc is not free
                allLocked.awaitUninterruptibly(); // reawake as soon as some thread reawakens
            }
            isPCFree.set(pos, false);

            labLock.readLock().lock(); // locking to block access from professors
        } finally { generalLock.unlock(); }
    }

    /** Unlocks a single specific pc. Used by students and thesis students. */
    public void singlePCUnlock(int pos){
        try{
            generalLock.lock();
            labLock.readLock().unlock();

            isPCFree.set(pos, true);
            allLocked.signalAll();
        } finally { generalLock.unlock(); }
    }

    /** Returns an index of a free pc. */
    private int getFreePosition(){
        for(int i = 0; i < numPC; i++)
            if(isPCFree.get(i))
                return i;
        
        return -1; // no pc is free
    }

    /** Returns whether the pos pc is free. */
    private boolean isFree(int pos){
        return isPCFree.get(pos);
    }
    
    /** Returns whether all pcs are free. */
    private boolean allPCsFree(){
        for(int i = 0; i < numPC; i++)
            if(!isFree(i)) return false;
        
        return true;
    }
}