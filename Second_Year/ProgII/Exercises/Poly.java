/**
 * A Poly is an immutable polynomial with integer coefficient.
 * A typical element is 
 *          c_0 + c_1x + c_2x^2 + ...  
 */
public class Poly {
    /**
     * @effects: makes a new Poly = 0
     */
    public Poly() { }

    /**
     * @throws: NegExponentException if n < 0
     * @effects: makes a new Poly = cx^n
     */
    public Poly(int c, int n) { }

    /**
     * @returns: the degree of this,
     *      the greatest exponent with a
     *      non-zero coefficient.
     *      Returns 0 if this = 0. 
     */
    public int degree() { }

    /**
     * @throws: NegExponentException if n < 0
     * @returns: the coefficient of the term
     *      of this whose exponent is n.
     */
    public int coeff(int n) { }

    /**
     * @returns: this + p
     */
    public Poly add(Poly p) { }

    /**
     * @returns: this * p
     */
    public Poly mult(Poly p) { }
    
}