package microblog.datastructs;

/**
 * Overview:
 *      A StringIntegerPair is an immutable data structure containing a String and an Integer,
 *      with the unique property that StringIntegerPairs can be compaired with respect to the Integer field.
 * Typical element:
 *      A pair < s, n > where s is a string and n is an integer.
 */
public class StringIntegerPair implements Comparable<StringIntegerPair> {
    /**
     * AF(c) = < s, n > where s is a string and n is an integer.
     */
    /**
     * RI: string != null && integer != null 
     */
    private final String string;
    private final Integer integer;

    /**
     * @requires: s != null && n != null
     * @throws:     NullPointerException is thrown if either s or n are null
     * @effects:    creates a new StringIntegerPair with the given parameters
     */
    public StringIntegerPair(String s, Integer n) throws NullPointerException {
        if (s == null || n == null)
            throw new NullPointerException("the given string and integer must not be null");
        string = s;
        integer = n;
    }

    /**
     * @effect: returns the string component of this
     */
    public String getString() {
        return string;
    }

     /**
     * @effect: returns the integer component of this
     */
    public Integer getInteger() {
        return integer;
    }

     /**
     * @effect: compares this to pair and returns 
     *              - a negative number if the integer field of this is less than the integer field of pair
     *              - a positive number if the integer field of this is greater than the integer field of pair
     *              - zero if they are equal.
     */
    public int compareTo(StringIntegerPair pair){
        return integer.compareTo(pair.getInteger());
    }
}
