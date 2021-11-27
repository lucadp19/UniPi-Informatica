package microblog.posts;

import java.time.LocalDateTime;
import microblog.datastructs.PostType;

/**
 * Overview:
 *      A LikePost is an immutable data type representing a like in a Social Network,
 *      together with methods to retrieve information about the post.
 * Typical Element:
 *      The typical element of a LikePost is a post representing a like with its meta-information, such as:
 *          - its unique identifier
 *          - its author
 *          - the id of the liked post,
 *          - the timestamp at which it was created.
 */
public class LikePost extends AbstractPost implements Post {
    /**
     * AF(c) = < id, author, contents, timestamp > 
     *      where:
     *          - id represents the unique id of the post c,
     *          - author represents the author of the post c,
     *          - contents represents the id of the liked post,
     *          - timestamp is the timestamp at which c was created.
     */
    /**
     * RI :     author != null && contents != null 
     *      && postType != null && postType == PostType.LIKE
     *      &&  0 < contents.length() <= Post.MAX_POST_LENGTH
     *      &&  contents is an integer in string format
     *      &&  timestamp != null
     */
    
    /**
     * @requires:   author != null && timestamp != null
     * @throws:     NullPointerException is thrown if author or timestamp is null
     * @effects:    creates a new LikePost with the given id, author, liked id and timestamp
     */
    public LikePost(int id, String author, int likedPostId, LocalDateTime timestamp) throws NullPointerException {
        if(author == null)
            throw new NullPointerException("author must not be null");
        if(timestamp == null)
            throw new NullPointerException("timestamp must not be null");
        postType = PostType.LIKE;
        this.id = id;
        this.author = author;
        this.contents = Integer.toString(likedPostId);
        this.timestamp = timestamp;
        this.contentDescriptor = "Liked post's id";
    }

    /**
     * @requires:   author != null
     * @throws:     NullPointerException is thrown if author is null
     * @effects:    creates a new LikePost with the given id, author, liked id and this moment's timestamp
     */
    public LikePost(int id, String author, int likedPostId) throws NullPointerException {
        this(id, author, likedPostId, LocalDateTime.now());
    }
}

