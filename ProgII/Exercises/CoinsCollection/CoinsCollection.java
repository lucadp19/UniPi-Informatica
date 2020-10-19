public interface CoinsCollection {
    //  OVERVIEW: Una CoinsCollection è una collezione di monete dal valore di 50 centesimi, 1 o 2 euro.
    //          Il valore tipico è 
    //                              [v1*50C, v2*1E, v3*2E],
    //          dove v1, v2 e v3 sono interi positivi.

    public CoinsCollection createCC();
    /**  EFFECTS: returns a CoinsCollection with 0 coins of each kind.
    */

    public void addCoin(Integer coin) throws NullPointerException, IllegalArgumentException;
    /** 
     * REQUIRES: coin == 50 || coin == 100 || coin == 200.
     * THROWS: NullPointerException (unchecked) is thrown if coin == null;
     *          IllegalArgumentException (unchecked) is thrown if coin is not one of 50, 100 or 200.
     * MODIFIES: this.
     * EFFECTS: after the method is invoked, this cointains one more element of type coin.
    */

    public int balance();
    /** EFFECTS: returns the total balance of this; 
                that is, returns the sum of the values of all the coins contained in this.
    */

    public CoinsCollection makeChange(Integer amount) throws NullPointerException, IllegalArgumentException;
    /** REQUIRES: amount is a multiple of 50.
        THROWS: NullPointerException (unchecked) is thrown if amount == null;
                IllegalArgumentException (unchecked) is thrown if amount is not a multiple of 50.
        MODIFIES: this.
        EFFECTS: returns a new CoinsCollection with total balance equal to amount e removes the coins used from this.
                If there aren't enough coins in this, this isn't modified and this method returns null.
    */
}