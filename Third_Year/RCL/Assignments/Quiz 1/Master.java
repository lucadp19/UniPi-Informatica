public class Master {
  public static void main(String[] args) throws InterruptedException {
    Thread.currentThread().setName("Master ");
    Thread worker = new Worker();
    worker.setName("Worker ");
    worker.start();
    Thread.currentThread().join();
    System.out.println(Thread.currentThread().getName());
}
  }