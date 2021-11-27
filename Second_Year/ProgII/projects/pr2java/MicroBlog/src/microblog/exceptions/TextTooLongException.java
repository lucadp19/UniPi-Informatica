package microblog.exceptions;

// An exception for texts whose length exceends the limit.
public class TextTooLongException extends Exception {
    public TextTooLongException(){
        super();
    }

    public TextTooLongException(String e){
        super(e);
    }
}
