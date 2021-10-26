/** An AbstractUser represents a general user of the lab */
public abstract class AbstractUser implements Runnable {
    protected int id; /** identifier of the user */
    protected int numTask; /** number of task the user has to do */
    protected int numDoneTask; /** number of tasks already done by the user */

    public abstract void run();

    /**
     * Checks if the user has finished working on his tasks.
     */
    public boolean isDone(){
        return (numTask - numDoneTask == 0);
    }
}
