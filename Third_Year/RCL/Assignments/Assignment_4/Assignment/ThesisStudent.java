import java.util.concurrent.ThreadLocalRandom;

public class ThesisStudent extends AbstractUser {
    private final int minWaitingTime = 50;
    private final int maxWaitingTime = 1000;
    private int labPos;
    private Lab lab;

    public ThesisStudent(int id, int numTask, int labPos, Lab lab){ 
        this.id = id;
        this.lab = lab;
        this.labPos = labPos;
        this.numTask = numTask;
        this.numDoneTask = 0;
        this.waiting = false;
    }

    public void run(){
        try {
            setWaiting(true); // is waiting for pc
            try{
                lab.singlePCLock(labPos); // locks only the specific pc
            } catch(InterruptedException e){
                System.out.printf("[TS] Thesis Student %d: brutally thrown out of the lab before entering.\n", id);
            }

            System.out.printf("[TS] Thesis Student %d: managed to get a hold of PC no. %d.\n", id, labPos);
            int waitingTime = ThreadLocalRandom.current().nextInt(minWaitingTime, maxWaitingTime);
            try{ 
                Thread.sleep(waitingTime);
            } catch(InterruptedException e) {
                System.out.printf("[TS] Thesis Student %d: brutally thrown out of the lab.\n", id);
            }
            numDoneTask++;
            System.out.printf("[TS] Thesis Student %d: task %d out of %d completed!\n", id, numDoneTask, numTask);
            
            setWaiting(false); // not waiting anymore
        } finally{ lab.singlePCUnlock(labPos); }
    }
}
