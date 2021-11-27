import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.ThreadLocalRandom;

public class BankAccountCreator {
    private static final long infName = 0;
    private static final long supName = 1000000;
    private static final Date endDate = new Date();
    private static final Date startDate = getStartDate();
    private static final int  minMovements = 30;
    private static final int  maxMovements = 300;

    public static BankAccount generateNewBankAccount(){
        // creating new bank account
        long id = generateNewName();
        BankAccount ba = new BankAccount(id);
        
        int movements = ThreadLocalRandom.current().nextInt(minMovements, maxMovements);
        for(int i = 0; i < movements; i++) {
            ba.addMovement(
                Causal.generateCausal(), 
                generateDate()
            );
        }
        
        return ba;
    }

    private static long generateNewName(){
        return ThreadLocalRandom.current().nextLong(infName, supName);
    }

    private static String generateDate(){
        long time = ThreadLocalRandom.current().nextLong(startDate.getTime(), endDate.getTime());
        Date date = new Date(time);
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return df.format(date); 
    }   

    // returns today's date, but 2 years ago
    private static Date getStartDate(){
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.YEAR, -2);
        return cal.getTime();
    }
}