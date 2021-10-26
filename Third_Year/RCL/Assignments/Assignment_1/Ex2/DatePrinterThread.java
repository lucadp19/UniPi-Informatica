import java.util.Calendar;
import java.text.SimpleDateFormat;

public class DatePrinterThread extends Thread {
    public static void main(String[] args) {
        DatePrinterThread dpt = new DatePrinterThread();
        dpt.start();
        System.out.println("Main thread: " + Thread.currentThread());
    }

    public void run(){
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
