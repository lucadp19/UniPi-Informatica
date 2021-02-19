public class Point {
    private int x, y;

    public Point(int x0, int y0){
        x = x0;
        y = y0;
    }

    public int squared_norm(){
        return pow(x, 2) + pow(y, 2);
    }

    public void add(Point p){
        x += p.x;
        y += p.y;
    }

    public Point sum(Point p){
        Point res = new Point(x + p.x, y + p.y);
        return res;
    }

    public String toString(){
        return "("+ x + ", " + y + ")"; 
    }

    private int pow(int base, int exp){
        int res = 1;
        for(int i = 0; i < exp; i++){
            res *= base;
        } return res;
    }
}