/**
     * @overview: A Game is a competition with a fixed number of athletes.
     *      The typical element is 
     *          { p_1 :: res_1, ..., p_dim :: res_dim },
     *      where dim is the number of athletes,
     *      p_1, ..., p_dim are the numbers linked to each athlete anc
     *      res_1, ..., res_dim are the results of each athlete.
     */
public interface Game<V extends Comparable>{
    /**
     * @requires: res != null && 1 <= num <= dim
     * @throws: NullPointerException if res = null
     * @modifies: this
     * @effects: sets the result of athlete p_num to res
     */
    public void setResult(int num, V res);
    
    /**
     * @effects: returns the index of the athlete in the first position.
     *      If more than one athlete is first, the method returns the one with the lowest index.
     *      If no athletes have yet competed, the method returns -1.
     */
    public int first();
    
    /**
     * @effect: returns the list of all the results up to that moment. * @return
     */
    public List<V> results();
}