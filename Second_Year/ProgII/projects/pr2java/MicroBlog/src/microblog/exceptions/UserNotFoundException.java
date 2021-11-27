package microblog.exceptions;

// An exception for users not already signed up.
public class UserNotFoundException extends Exception {
    public UserNotFoundException(){
        super();
    }

    public UserNotFoundException(String e){
        super(e);
    }
}