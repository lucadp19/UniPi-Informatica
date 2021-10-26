import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * DatePrinter
 */
public class DatePrinter {
    public static void main(String[] args) {
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