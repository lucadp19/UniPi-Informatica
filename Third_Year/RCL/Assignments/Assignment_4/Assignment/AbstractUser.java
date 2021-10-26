/** An AbstractUser represents a general user of the lab */
public abstract class AbstractUser implements Runnable {
    protected int id;           /** identifier of the user */
    protected int numTask;      /** number of task the user has to do */
    protected int numDoneTask;  /** number of tasks already done by the user */
    protected boolean waiting;  /** whether the user is already waiting to enter the lab */

    public abstract void run();

    /**
     * Checks if the user has finished working on his tasks.
     */
    public boolean isDone(){
        return (numTask - numDoneTask <= 0);
    }

    /**
     * Sets the waiting status.
     */
    public void setWaiting(boolean val){
        waiting = val;
    }

    /**
     * Checks if the user is waiting for a free pc.
     */
    public boolean isWaiting(){
        return waiting;
    }
}
