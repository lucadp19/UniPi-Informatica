import java.io.*;
import java.nio.ByteBuffer;
import java.nio.channels.AcceptPendingException;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicIntegerArray;

import com.google.gson.*;
import com.google.gson.stream.*;

public class Assignment {
    /** Runnable instance for counting causals */
    public static class BankCounter implements Runnable {
        BankAccount account;
        private AtomicIntegerArray counters;

        public BankCounter(BankAccount account, AtomicIntegerArray counters){
            if(counters.length() != Causal.numberOfCausals()) // checking that the array has the correct length
                throw new IllegalArgumentException();
            this.counters = counters;
            this.account = account;
        }

        public void run(){
            List<BankAccount.Movement> movements = account.getMovements();

            // using the numbering of the causals to avoid the huge switch
            for(BankAccount.Movement movement : movements)
                counters.getAndIncrement(movement.causal.ordinal());
        }
    }

    private static final String ACCOUNTS_FILE = "accounts.json";
    private static final int minAccounts = 10;
    private static final int maxAccounts = 100;
    private static final long terminationDelay = 3000;

    public static void main(String[] args) {
        System.out.println("> Generating JSON file!");
        writeFile();
        System.out.println("> JSON file generated! Starting read...");

        // creating server pool
        AtomicIntegerArray counters = new AtomicIntegerArray(Causal.numberOfCausals());
        ExecutorService pool = Executors.newFixedThreadPool(10);

        try (
            FileInputStream inputStream = new FileInputStream(ACCOUNTS_FILE);
            JsonReader reader = new JsonReader(new InputStreamReader(inputStream));
        ) {
            Gson gson = new GsonBuilder().create();
            // starting reading the list of accounts
            reader.beginArray();
            while(reader.hasNext()){
                BankAccount account = gson.fromJson(reader, BankAccount.class);
                pool.execute(new BankCounter(account, counters));
            }
            reader.endArray();
        } catch(IOException ex) {
            System.err.println("IO Exception caught.");
            ex.printStackTrace();
            System.exit(-1);
        }

        pool.shutdown();
        try {
            if(!pool.awaitTermination(terminationDelay, TimeUnit.MILLISECONDS))
                pool.shutdownNow();
        } catch(InterruptedException e){
            pool.shutdownNow();
        }

        // printing stats
        System.out.println("> Data read!\n\n\t -- STATS --");
        for(int i = 0; i < Causal.numberOfCausals(); i++)
            System.out.println("Causal: \"" + Causal.getCausal(i) + "\" found " + counters.get(i) + " times.");
    }

    private static void writeFile(){
        int noAccounts = ThreadLocalRandom.current().nextInt(minAccounts, maxAccounts);
        Gson gson = new GsonBuilder().setPrettyPrinting().create();

        try (
            FileOutputStream outStream = new FileOutputStream(ACCOUNTS_FILE);
            FileChannel outChannel = outStream.getChannel();
        ) {
            ByteBuffer buf = ByteBuffer.allocateDirect(1024);
            buf.put("[".getBytes(StandardCharsets.US_ASCII)); // starts the list of accounts
            
            // I don't know why but without the "flush" everything breaks
            buf.flip();
            while(buf.hasRemaining()) outChannel.write(buf);
            buf.compact();
                    
            for(int i = 0; i < noAccounts; i++){
                BankAccount account = BankAccountCreator.generateNewBankAccount();
                String accountGson = gson.toJson(account);
                byte[] accountBytes = accountGson.getBytes(StandardCharsets.US_ASCII);

                int position = 0; // marks the first not-written byte

                while(true){
                    // calculating number of bytes to write
                    int remainingLen = accountBytes.length - position;

                    if(remainingLen <= 0) break;
                    // putting as much bytes as possible into buf
                    buf.put(accountBytes, position, Math.min(remainingLen, buf.remaining()));
                    
                    // flipping
                    buf.flip();
                    outChannel.write(buf);
                    // updating position with the data of the new read
                    position += buf.position();
                    buf.compact();
                }
                // adding a comma between accounts in the JSON file
                if(i != noAccounts - 1) {
                    // I don't know why but without the "flush" everything breaks
                    buf.flip();
                    while(buf.hasRemaining()) outChannel.write(buf);
                    buf.compact();
                    
                    buf.put(",".getBytes(StandardCharsets.US_ASCII));
                    
                    // I don't know why but without the "flush" everything breaks
                    buf.flip();
                    while(buf.hasRemaining()) outChannel.write(buf);
                    buf.compact();
                }
            }
            // closing array of accounts
            buf.put("]".getBytes(StandardCharsets.US_ASCII));

            // writing remaining data
            buf.flip();
            while(buf.hasRemaining()) outChannel.write(buf);
        } catch(FileNotFoundException ex) {
            System.err.println("The JSON file " + ACCOUNTS_FILE + " could not be created.");
            ex.printStackTrace();
            System.exit(1);
        } catch(IOException ex) {
            System.err.println("IO Exception caught.");
            ex.printStackTrace();
            System.exit(1);
        }
    }
}
