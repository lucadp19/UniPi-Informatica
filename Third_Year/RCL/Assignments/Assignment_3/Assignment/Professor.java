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
    }

    public void run(){
        try {
            lab.lockEntireLab(); // locks the entire lab
            System.out.printf("[P] Professor %d: managed to get a hold of the lab.\n", id);
            int waitingTime = ThreadLocalRandom.current().nextInt(minWaitingTime, maxWaitingTime);
            try{ 
                Thread.sleep(waitingTime);
            } catch(InterruptedException e) {
                System.out.printf("[P] Professor %d: brutally thrown out of the lab.\n", id);
            }
            numDoneTask++;
            System.out.printf("[P] Professor %d: task %d out of %d completed!\n", id, numDoneTask, numTask);
        } finally{ lab.unlockEntireLab(); }
    }
}
