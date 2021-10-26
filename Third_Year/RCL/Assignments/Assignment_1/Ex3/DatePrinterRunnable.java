import java.text.SimpleDateFormat;
import java.util.Calendar;

public class DatePrinterRunnable implements Runnable {
    public static void main(String[] args) {
        Thread thread = new Thread(new DatePrinterRunnable());
        thread.start();
        System.out.println("Main thread: " + Thread.currentThread());
    }

    @Override
    public void run() {
        while(true){
            Calendar cal = Calendar.getInstance();
            SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd H:m:s");
            System.out.println(format.format(cal.getTime()));
            System.out.println(Thread.currentThread());
            try { Thread.sleep(2000); }
            catch(InterruptedException e) {
                e.printStackTrace();
                System.out.println("Execution interrupted.");
            }
        } 
    }
}
