import java.util.ArrayList;
import java.util.List;

public class ArrayGame<V extends Comparable> implements Game<V> {
    
    private int firstIndex;
    private V[] res;

    /* AF: a(firstIndex, res) = 
     *          f : [1, ..., res.length + 1] -> V
     *      tale che f(i) = res[i - 1] se res[i - 1] è diverso da null,
     *      indefinito altrimenti. 
     */
    /* RI: res != null &&
     *      1 <= firstIndex <= res.length &&
     *     (forall i. 0 <= i < res.length ==> res[i] == null || res[firstIndex - 1] >= res[i]) &&
     *     (forall i. 0 <= i < firstIndex - 1 ==> res[i] == null || res[firstIndex - 1] > res[i]).
     */

    public ArrayGame(int numAthletes) throws IllegalArgumentException {
        if(numAthletes <= 0) 
            throw  new IllegalArgumentException();
        this.res = (V[]) new Object[numAthletes];
        firstIndex = -1;
    }

    /**
     * @requires: res != null && 1 <= num <= dim
     * @throws: NullPointerException if res = null
     * @modifies: this
     * @effects: sets the result of athlete p_num to res
     */
    public void setResult(int num, V res) throws NullPointerException, IllegalArgumentException {
        if(res == null)
            throw new NullPointerException();
        if(num < 1 || num > res.length)
            throw new IllegalArgumentException();
        
        this.res[num - 1] = res;
        this.updateFirst(num - 1);
    }
    
    /**
     * @effects: returns the index of the athlete in the first position.
     *      If more than one athlete is first, the method returns the one with the lowest index.
     *      If no athletes have yet competed, the method returns -1.
     */
    public int first(){
        return firstIndex;
    }
    
    /**
     * @effect: returns the list of all the results up to that moment. * @return
     */
    public List<V> results(){
        List<V> list = new ArrayList<V>();

        for(V result : res){
            list.add(result);
        }
        return list;
    }

    private void updateFirst(int pos) {
        if(firstIndex == -1 
            || res[pos].compareTo(res[firstIndex - 1]) > 0
            || (res[pos].compareTo(res[firstIndex - 1]) == 0 
                    && pos <= firstIndex - 1))
            firstIndex = pos + 1;      
    }
}
