package microblog.posts;

import java.time.LocalDateTime;
import java.util.Set;
import microblog.datastructs.PostType;

/**
 *  Overview:
 *      A Post is an immutable interface for an event (such as a textual post, or a like) happened in a social network,
 *      with methods to get the information stored in the post.
 *  Typical Element:
 *      The typical element of a Post is a post with its meta-information, such as:
 *          - its type (it can be a text post, or a report, or a like)
 *          - its unique identifier
 *          - its author
 *          - its content
 *          - the timestamp at which it was created.
 */
public interface Post {
    // The maximum length of the content of a post.
    public static final int MAX_POST_LENGTH = 140;

    /**
     * @effects: returns the type of this
     */
    public PostType getPostType();

    /**
     * @effects: returns the id of this
     */
    public int getId();

    /**
     * @effects: returns the author of this
     */
    public String getAuthor();

    /**
     * @effects: returns the text contents of this
     */
    public String getContents();

    /**
     * @effects: returns the timestamp of this
     */
    public LocalDateTime getTimestamp();
}