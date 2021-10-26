public class ThreadTest implements Runnable{
    public static void main(String[] args) {
        Thread thread = new Thread(new ThreadTest());
        thread.run(); // LINE A
        try {
            thread.join();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    public void run() {
        for (int i = 2; i <= 10; i = i + 2) {
            System.out.print(i);
        }
    }
    
}