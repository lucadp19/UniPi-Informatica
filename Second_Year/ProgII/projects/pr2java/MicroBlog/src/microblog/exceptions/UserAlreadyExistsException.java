package microblog.exceptions;

// An exception for signing up users with already existing usernames.
public class UserAlreadyExistsException extends Exception {
    public UserAlreadyExistsException(){
        super();
    }

    public UserAlreadyExistsException(String e){
        super(e);
    }
}
