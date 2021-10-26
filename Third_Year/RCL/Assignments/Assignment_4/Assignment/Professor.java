import java.util.concurrent.ThreadLocalRandom;

public class Professor extends AbstractUser {
    private final int minWaitingTime = 500;
    private final int maxWaitingTime = 3000;
    private Lab lab;

    public Professor(int id, int numTask, Lab lab){ 
        this.id = id;
        this.lab = lab;
        this.numTask = numTask;
        this.numDoneTask = 0;
        this.waiting = false;
    }

    public void run(){
        try {
            setWaiting(true); // is waiting for the lab to be free
            
            try { 
                lab.lockEntireLab(); // locks the entire lab
            } catch(InterruptedException e){ 
                System.out.printf("[P] Professor %d: thrown out of the lab before entering.\n", id); 
            }

            System.out.printf("[P] Professor %d: managed to get a hold of the lab.\n", id);
            int waitingTime = ThreadLocalRandom.current().nextInt(minWaitingTime, maxWaitingTime);
            try{ 
                Thread.sleep(waitingTime);
            } catch(InterruptedException e) {
                System.out.printf("[P] Professor %d: brutally thrown out of the lab.\n", id);
            }
            numDoneTask++;
            System.out.printf("[P] Professor %d: task %d out of %d completed!\n", id, numDoneTask, numTask);
            setWaiting(false);
        } finally{ lab.unlockEntireLab(); }
    }
}
