import java.util.*;
import java.util.concurrent.locks.*;

public class Lab {
    private static final int defaultNumPC = 20;

    private boolean locked;
    private int numPC;                      /** number of pcs in the lab */
    private List<Boolean> isPCFree;         /** keeps track of which pcs are free*/

    public Lab(){ this(Lab.defaultNumPC); }
    public Lab(int numPC){ 
        this.numPC = numPC; 

        isPCFree = new ArrayList<Boolean>(numPC);

        this.locked = false;
        for(int i = 0; i < numPC; i++) {
            isPCFree.add(true); // all pcs are free at the start
        }
    }

    /** Locks the entire lab. Used by professors. */
    public synchronized void lockEntireLab() throws InterruptedException { 
        while(!allPCsFree() || locked) // checks if all pcs are free
            this.wait(); // as soon as one is freed, this thread reawakens
        
        locked = true; // lab is set to locked
    }

    /** Unlocks the lab after a lockEntireLab. */
    public synchronized void unlockEntireLab(){ 
        locked = false; // lab is unlocked
        this.notifyAll();
    }

    /** Locks a non-specified pc in reader mode. Used by students. */
    public synchronized int singlePCLock() throws InterruptedException {
        int pos;

        while(locked || ((pos = getFreePosition()) == -1)) // no pc are free
            this.wait(); // as soon as one is free, this thread reawakens
        isPCFree.set(pos, false);

        return pos; // returns the occupied pc
    }

    /** Locks a specific pc. Used by thesis students. */
    public synchronized void singlePCLock(int pos) throws InterruptedException {
        while(locked || !isFree(pos)) { // the pos pc is not free
            this.wait(); // reawake as soon as some thread reawakens
        }
        isPCFree.set(pos, false);
    }

    /** Unlocks a single specific pc. Used by students and thesis students. */
    public synchronized void singlePCUnlock(int pos){
        isPCFree.set(pos, true);
        this.notifyAll();
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