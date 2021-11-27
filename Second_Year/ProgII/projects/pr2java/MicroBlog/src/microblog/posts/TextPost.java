package microblog.posts;

import java.time.LocalDateTime;

import microblog.exceptions.*;
import microblog.datastructs.PostType;

/**
 *  Overview: 
 *      A TextPost is an immutable post with text content, together with methods to get information about
 *      the author of the post, its content and more.
 *  Typical Element:
 *      The typical element of an TextPost is a textual post with its meta-information, such as:
 *          - its unique identifier
 *          - its author
 *          - its text content
 *          - the timestamp at which it was created.
 */
public class TextPost extends AbstractPost implements Post {
    /**
     * AF(c) = < id, author, contents, timestamp > 
     *      where:
     *          - id represents the unique id of the post c,
     *          - author represents the author of the post c,
     *          - contents represents the textual content of c,
     *          - timestamp is the timestamp at which c was created.
     */
    /**
     * RI :     author != null && contents != null 
     *      && postType != null && postType == PostType.TEXT
     *      &&  0 < contents.length() <= Post.MAX_POST_LENGTH
     *      &&  timestamp != null
     */
    
    
    /**
     * @requires:   author != null && contents != null && timestamp != null && 0 < contents.length() <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException is thrown if author, timestamp or contents is null,
     *              TextTooLongException is thrown if contents.length() exceeds Post.MAX_POST_LENGTH,
     *              EmptyTextException is thrown if contents is empty
     * @effects:    creates a new post with the given id, author, text and timestamp
     */
    public TextPost(int id, String author, String contents, LocalDateTime timestamp) throws NullPointerException, TextTooLongException, EmptyTextException {
        if (author == null || contents == null)
            throw new NullPointerException("author and contents of the post must not be null.");
        if (timestamp == null)
            throw new NullPointerException("timestamp must not be null.");
        if (contents.isEmpty())
            throw new EmptyTextException("the text of a post must not be empty");
        if (contents.length() > Post.MAX_POST_LENGTH)
            throw new TextTooLongException("the text of a post cannot exceed " + Post.MAX_POST_LENGTH + " characters.");
    
        this.postType = PostType.TEXT;
        this.id = id;
        this.author = author;
        this.contents = contents;
        this.timestamp = timestamp;
        this.contentDescriptor = "Text";
    }

    /**
     * @requires:   author != null && contents != null && 0 < contents.length() <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException is thrown if author or contents is null,
     *              TextTooLongException is thrown if contents.length() exceeds Post.MAX_POST_LENGTH,
     *              EmptyTextException is thrown if contents is empty
     * @effects:    creates a new post with the given id, author, text and this moment's timestamp
     */
    public TextPost(int id, String author, String contents) throws NullPointerException, TextTooLongException, EmptyTextException {
        this(id, author, contents, LocalDateTime.now());
    }
}
