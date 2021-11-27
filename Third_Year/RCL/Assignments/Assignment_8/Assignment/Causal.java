import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public enum Causal {
    Bonifico, 
    Accredito, 
    Bollettino, 
    F24, 
    PagoBancomat;

    private static final Causal[] vals = Causal.values();

    public static Causal generateCausal(){
        return vals[
            ThreadLocalRandom.current().nextInt(0, vals.length)
        ];
    }

    public static Causal getCausal(int i){
        if(i < 0 || i >= vals.length) throw new IndexOutOfBoundsException();
        return vals[i];
    }

    public static int numberOfCausals(){
        return vals.length;
    }
}