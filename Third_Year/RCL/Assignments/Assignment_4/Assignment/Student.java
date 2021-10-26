import java.util.concurrent.ThreadLocalRandom;

public class Student extends AbstractUser {
    private final int minWaitingTime = 20;
    private final int maxWaitingTime = 500;
    private Lab lab;

    public Student(int id, int numTask, Lab lab){ 
        this.id = id;
        this.lab = lab;
        this.numTask = numTask;
        this.numDoneTask = 0;
        this.waiting = false;
    }

    public void run(){
        int pos = -1;
        try {
            setWaiting(true); // waiting for a free pc
            
            try{
                pos = lab.singlePCLock(); // locks only the specific pc
            } catch(InterruptedException e){
                System.out.printf("[S] Student %d: brutally thrown out of the lab before entering.\n", id);
            }

            System.out.printf("[S] Student %d: managed to get a hold of PC no. %d.\n", id, pos);
            int waitingTime = ThreadLocalRandom.current().nextInt(minWaitingTime, maxWaitingTime);
            try{ 
                Thread.sleep(waitingTime);
            } catch(InterruptedException e) {
                System.out.printf("[S] Student %d: brutally thrown out of the lab.\n", id);
            }
            numDoneTask++;
            System.out.printf("[S] Student %d: task %d out of %d completed!\n", id, numDoneTask, numTask);

            setWaiting(false); // not waiting anymore
        } finally{ if(pos != -1) lab.singlePCUnlock(pos); }
    }
}
