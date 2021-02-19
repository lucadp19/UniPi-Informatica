public class Main {
    public static void main(String args[]){
        Point a = new Point(1, 0);
        Point b = new Point(0, 2);
        Point c = a.sum(b);
        System.out.println(a.toString() + " + " + b + " = " + c);
        System.out.println("The squared norm of the third point is: " + Integer.toString(c.squared_norm()));
    }
}