import java.util.List;
import java.util.ArrayList;

public class ListCC implements CoinsCollection {
    //  OVERVIEW: Una CoinsCollection è una collezione di monete (mutable) dal valore di 50 centesimi, 1 o 2 euro.
    //          Il valore tipico è 
    //                              [v1*50C, v2*1E, v3*2E],
    //          dove v1, v2 e v3 sono interi positivi.

    private List<Integer> coins;
    private List<Integer> values;
    private int totalAmount;

    // AF: ordered tuple (v1, v2, v3) where 
    //      v1 is the number of 50 cents coins, 
    //      v2 is the number of 1 euro coins and 
    //      v3 is the number of 2 euro coins
    // RI: coins != null && totalAmount >= 0 &&
    //      forall i. 0 <= i < 3 ==> (coins.get(i) != null && coins.get(i) >= 0) &&
    //      totalAmount == sum_{i = 0, 1, 2} coins.get(i)

    public ListCC(){
        this(0, 0, 0);
    }

    public ListCC(int v1, int v2, int v3) throws IllegalArgumentException {
        /**
         * REQUIRES: v1, v2, v3 >= 0
         * THROWS: IllegalArgumentException is thrown if either one of v1, v2 or v3 is negative
         * EFFECTS: creates a new ListCC with v1 "50 cents" coins, v2 "1 euro" coins and v3 "2 euro" coins.
         */
        if(v1 < 0 || v2 < 0 || v3 < 0)
            throw new IllegalArgumentException();
        
        coins = new ArrayList<Integer>(3);
        coins.add(v1);
        coins.add(v2);
        coins.add(v3);

        values = new ArrayList<Integer>(3);
        values.add(50);
        values.add(100);
        values.add(200);

        totalAmount = v1*50 + v2*100 + v3*200;
    }

    public CoinsCollection createCC(){
        /**  
         * EFFECTS: returns a CoinsCollection with 0 coins of each kind.
         */
        return new ListCC();
    }

    public void addCoin(Integer coin) throws NullPointerException, IllegalArgumentException{
        /** 
         * REQUIRES: coin == 50 || coin == 100 || coin == 200.
         * THROWS: NullPointerException (unchecked) is thrown if coin == null;
         *          IllegalArgumentException (unchecked) is thrown if coin is not one of 50, 100 or 200.
         * MODIFIES: this.
         * EFFECTS: after the method is invoked, this cointains one more element of type coin.
        */

        assert checkRep();

        if(coin == null)
            throw new NullPointerException();
        
        switch (coin.intValue()) {
            case 50:
                incrementBy(0, 1);
                break;
            case 100:
                incrementBy(1, 1);
                break;
            case 200:
                incrementBy(2, 1);
                break;
            default:
                throw new IllegalArgumentException();
        }

        assert checkRep();
    }

    public int balance(){
        /** EFFECTS: returns the total balance of this; 
         *          that is, returns the sum of the values of all the coins contained in this.
         */
        return totalAmount;
    }

    public CoinsCollection makeChange(Integer amount) throws NullPointerException, IllegalArgumentException {
        /** 
         * REQUIRES: amount is a multiple of 50.
         * THROWS: NullPointerException (unchecked) is thrown if amount == null;
         *          IllegalArgumentException (unchecked) is thrown if amount is not a multiple of 50.
         * MODIFIES: this.
         * EFFECTS: returns a new CoinsCollection with total balance equal to amount e removes the coins used from this.
         *          If there aren't enough coins in this, this isn't modified and this method returns null.
        */
        assert checkRep();    

        if(amount == null)
            throw new NullPointerException();
        if(amount.intValue()%50 != 0)
            throw new IllegalArgumentException();
        
        List<Integer> change = new ArrayList<Integer>(3);
        for(int i = 0; i < 3; i++)
            change.add(0);

        for(int i = 2; i >= 0; i--){
            change.set(i, Math.min(amount/values.get(i), coins.get(i)));
            amount = amount - change.get(i)*values.get(i);
        }

        if(amount != 0){
            return null;
        }

        for(int i = 0; i < 3; i++)
            incrementBy(i, -change.get(i));
        
        assert checkRep();   

        return new ListCC(change.get(2), change.get(1), change.get(1));
    }

    public String toString(){
        return "No. 50 cents: " + coins.get(0) + ", No. 1 euro: " + coins.get(1) + ", No. 2 euro: " + coins.get(2) + ".";
    }

    private void incrementBy(int idx, int incr) throws IndexOutOfBoundsException, IllegalArgumentException {
        /**
         * REQUIRES: idx \in {0, 1, 2} && (incr < 0 ==> incr + coins.get(idx) >= 0)
         * THROWS: IndexOutOfBoundsException is thrown if idx is not one of 0, 1 or 2
         *          IllegalArgumentException is thrown when incr is negative and (incr + coins.get(idx) < 0)
         * EFFECTS: adds incr to the value contained in coins[idx]
         */
        assert checkRep();

        if(idx < 0 || idx >= coins.size())
            throw new IndexOutOfBoundsException();
        if(incr < 0 && -incr > coins.get(idx))
            throw new IllegalArgumentException();

        coins.set(idx, coins.get(idx) + incr);
        totalAmount += incr*values.get(idx);

        assert checkRep();
    }

    private boolean checkRep() {
    // RI: coins != null && totalAmount >= 0 &&
    //      forall i. 0 <= i < 3 ==> (coins.get(i) != null && coins.get(i) >= 0) &&
    //      totalAmount == sum_{i = 0, 1, 2} coins.get(i)
        int sum = 0;
        
        if(coins == null){
            return false;
            // throw new ViolationRepInvariantException("coins == null");
        }
        if(totalAmount < 0){
            return false;
            // throw new ViolationRepInvariantException("totalAmount < 0");
        }
        for(int i = 0; i < 3; i++){
            if(coins.get(i) == null){
                return false;
                // throw new ViolationRepInvariantException("coins.get(i) == null");
            }
            if(coins.get(i) < 0){
                return false;
                // throw new ViolationRepInvariantException("coins.get(i) < 0");
            }
            sum += coins.get(i) * values.get(i);
        }

        if(sum != totalAmount){
            return false;
            // throw new ViolationRepInvariantException("totalAmount is not the sum of all the values");
        }
        
        return true;
    }

    private class ViolationRepInvariantException extends Exception {
        public ViolationRepInvariantException(){
            super();
        }
        public ViolationRepInvariantException(String s){
            super(s);
        }
    }
}
