package microblog.exceptions;

// An exception for posts not found.
public class IdNotFoundException extends Exception {
    public IdNotFoundException(){
        super();
    }

    public IdNotFoundException(String e){
        super(e);
    }
}
