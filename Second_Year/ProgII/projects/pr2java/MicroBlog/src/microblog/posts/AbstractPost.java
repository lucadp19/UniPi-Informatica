package microblog.posts;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import microblog.exceptions.*;
import microblog.datastructs.PostType;

/**
 * Overview:
 *      An AbstractPost is an immutable data type representing a generic post in a Social Network,
 *      together with methods to retrieve information about the post.
 * Typical Element:
 *      The typical element of an AbstractPost is a post with its meta-information, such as:
 *          - its type (it can be a text post, or a report, or a like)
 *          - its unique identifier
 *          - its author
 *          - its content
 *          - the timestamp at which it was created.
 */
public class AbstractPost implements Post {
    /**
     * AF(c) = < postType, id, author, contents, timestamp > 
     *      where:
     *          - postType is the type of the post c,
     *          - id represents the unique id of the post c,
     *          - author represents the author of the post c,
     *          - contents represents the contents of the post c,
     *          - timestamp is the timestamp at which c was created.
     */

    protected PostType postType;
    protected int id;
    protected String author;
    protected String contents;
    protected LocalDateTime timestamp;

    // contentDescriptor is used only to represent a post as a String.
    protected String contentDescriptor;
    
    // Specification given by the interface Post.
    public PostType getPostType(){
        return postType;
    }

    // Specification given by the interface Post.
    public int getId() {
        return id;
    }

    // Specification given by the interface Post.
    public String getAuthor(){
        return author;
    }

    // Specification given by the interface Post.
    public String getContents(){
        return contents;
    }

    // Specification given by the interface Post.
    public LocalDateTime getTimestamp(){
        return timestamp;
    }

    /**
     * @effects: returns a format for printing the timestamp
     */
    protected DateTimeFormatter getTimeFormat(){
        return DateTimeFormatter.ofPattern("HH:mm dd/MM/yyyy");
    }

    /**
     * @effects: returns a String version of this post
     */
    public String toString(){
        return "{ Post identified by: " + getId() + ".\n" +
                "\tType: " + getPostType() + ".\n" + 
                "\tAuthor: " + getAuthor() + ".\n" +
                "\tTimestamp: " + getTimestamp().format(getTimeFormat()) + ".\n" +
                "\t" + contentDescriptor + ": " + getContents() + ". }\n";
    }

    /**
     * @effects: returns true if and only if this and p are the same post
     */
    public boolean equals(Object obj){
        if (obj == null || obj.getClass() != this.getClass())
            return false;
        if (this == obj) 
            return true;
        
        Post p = (Post) obj;
        
        return (id == p.getId() &&
                postType == p.getPostType() &&
                author == p.getAuthor() &&
                contents == p.getContents() &&
                timestamp == p.getTimestamp());
    }
}
