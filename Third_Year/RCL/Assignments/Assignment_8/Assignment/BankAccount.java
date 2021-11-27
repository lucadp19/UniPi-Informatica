import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class BankAccount {
    public class Movement{
        public Causal causal;
        public String date;

        public Movement(Causal causal, String date){
            this.causal = causal;
            this.date   = date;
        }
    }

    private long id;
    private List<Movement> movements = new ArrayList<>();
    
    public BankAccount(long id){ this.id = id; }

    public void addMovement(Causal causal, String date){
        movements.add(new Movement(causal, date));
    }

    public List<Movement> getMovements(){
        return new ArrayList<Movement>(movements);
    }
}
