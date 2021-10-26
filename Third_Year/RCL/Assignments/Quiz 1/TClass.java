public class TClass{
public static void main(String args[]) throws Exception {
    Thread thread1 = new Thread();
    Thread thread2 = new Thread(new T());
    Thread thread3 = new Thread(new T(), "Thread3");
    Thread thread4 = new Thread("Thread4");
    thread1.run();    thread2.run();
    thread3.run();    thread4.run();
}
}