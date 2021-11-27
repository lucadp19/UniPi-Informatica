package microblog.exceptions;

// An exception for usernames containing not allowed characters.
public class IllegalUsernameException extends Exception {
    public IllegalUsernameException(){
        super();
    }

    public IllegalUsernameException(String e){
        super(e);
    }
}
