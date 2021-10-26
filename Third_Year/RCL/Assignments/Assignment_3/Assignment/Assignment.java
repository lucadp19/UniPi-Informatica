import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;

public class Assignment {
    public final static int minTasks = 2;
    public final static int maxTasks = 7;
    public final static int numPC = 20;

    public static void main(String[] args) {
        if(args.length != 3){
            System.err.println("There must be 3 additional arguments: the number of professors, thesis students and regular students.");
            System.exit(1);
        }

        int numProf = Integer.parseInt(args[0]);
        int numTS = Integer.parseInt(args[1]);
        int numStud = Integer.parseInt(args[2]);

        Lab lab = new Lab(numPC);

        int totUsers = numProf + numTS + numStud;
        List<AbstractUser> users = new ArrayList<>(totUsers);

        for(int i = 0; i < numProf; i++)
            users.add(new Professor(
                i, 
                ThreadLocalRandom.current().nextInt(minTasks, maxTasks),
                lab
            ));
        for(int i = 0; i < numTS; i++)
            users.add(new ThesisStudent(
                i, 
                ThreadLocalRandom.current().nextInt(minTasks, maxTasks), 
                ThreadLocalRandom.current().nextInt(0, 20),
                lab
            ));
        for(int i = 0; i < numStud; i++)
            users.add(new Student(
                i, 
                ThreadLocalRandom.current().nextInt(minTasks, maxTasks), 
                lab
            ));
        
        ExecutorService pool = Executors.newFixedThreadPool(numPC); 
        Collections.shuffle(users); // shuffling users so that profs/TSs aren't all at the beginning
        
        boolean done = false;
        while(!done){
            done = true;
            for(AbstractUser user : users){
                if(!user.isDone()){
                    done = false;
                    pool.execute(user);
                    try { Thread.sleep(50); }
                    catch(InterruptedException e){ 
                        System.err.println("Interrupted!"); 
                        System.exit(1);
                    }
                }
            }
        }
        
        pool.shutdown();
    }
}
