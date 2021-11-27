package microblog.exceptions;

// An exception for empty text fields.
public class EmptyTextException extends Exception {
    public EmptyTextException(){
        super();
    }

    public EmptyTextException(String e){
        super(e);
    }
}
