public class Counter {
    private int counter;

    public Counter(){ counter = 0; }
    public Counter(int initValue){ counter = initValue; }

    public int get(){ return counter; }
    public void increment(){ counter++; }
}
