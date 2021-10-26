import java.util.ArrayList;
import java.util.concurrent.*;

public class Power implements Callable<Double> {
    private double n;
    private int exp;

    public Power(double n, int exp){
        this.n = n;
        this.exp = exp;
    }

    public Double call() throws Exception{
        if(exp < 2 || exp > 50) throw new Exception("Esponente fuori limite.");

        System.out.printf("Esecuzione %f^%d in %d.\n", n, exp, Thread.currentThread().getId());
        return Math.pow(n, exp);
    }

    public static void main(String[] args) {
        if(args.length < 1){
            System.err.println("Il programma richiede la base del numero da elevare a potenza.");
            System.exit(1);
        }

        double n = Double.parseDouble(args[0]);
        ExecutorService pool = Executors.newCachedThreadPool();
        ArrayList<Future<Double>> tasks = new ArrayList<>();
        for(int exp = 2; exp <= 50; exp++){
            tasks.add(pool.submit(new Power(n, exp)));
        }

        double ans = 0;
        try{ 
            for(Future<Double> task : tasks)
                ans += task.get();
        } catch(Exception e){
            e.printStackTrace();
        }

        pool.shutdown();
        System.out.println("Il risultato è " + ans + ".");
    }
}
