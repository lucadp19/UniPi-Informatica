package microblog.exceptions;

// An exception for self-likes or likes to already-liked-posts.
public class IllegalLikeException extends Exception {
    public IllegalLikeException(){
        super();
    }

    public IllegalLikeException(String e){
        super(e);
    }
}
