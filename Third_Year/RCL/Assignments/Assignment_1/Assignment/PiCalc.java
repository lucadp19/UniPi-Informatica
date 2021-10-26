public class PiCalc implements Runnable {
    private double accuracy; /** Accuracy to reach */
    private double pi;       /** Estimate for pi */
    private int steps;       /** Number of steps done */
    private short sign;      /** Sign of next term */
    
    public static void main(String[] args) {
        if(args.length != 2){
            System.out.println("Error: two arguments are needed.");
            return;
        }

        double accuracy;
        int timeout;
        try {
            accuracy = Double.parseDouble(args[0]);
            timeout = Integer.parseInt(args[1]);
        } catch (Exception e){
            e.printStackTrace();
            return;
        }

        PiCalc calc = new PiCalc(accuracy);
        Thread calcTh = new Thread(calc);     
        calcTh.start();

        // try to join thread before timeout
        // this may happen only if the threshold is reached
        try { calcTh.join(timeout); }
        catch(InterruptedException e){
            e.printStackTrace();
            return;
        }
        calcTh.interrupt();

        System.out.println("Estimated value for pi: " + calc.getPi());
    }

    PiCalc(double accuracy){
        this.accuracy = accuracy;
        this.pi = 0;
        this.steps = 0;
        this.sign = 1;
    }

    @Override
    public void run() {
        while(true){
            pi += (sign*4.0)/(2*steps + 1);
            sign *= -1;
            steps++;
            
            // thread interrupted by main thread
            if(Thread.currentThread().isInterrupted()){
                System.out.println("Thread interrupted.");
                break;
            } 
            // accuracy threshold reached
            if(Math.abs(pi - Math.PI) < accuracy){
                System.out.println("Accuracy threshold reached.");
                break;
            }
        }
    }

    public double getPi(){
        return this.pi;
    }
    
}