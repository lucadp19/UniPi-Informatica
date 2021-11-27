package microblog.posts;

import java.time.LocalDateTime;

import microblog.exceptions.*;
import microblog.datastructs.PostType;

/**
 *  Overview:
 *      A ReportPost is a post that contains the information about a report in a social network,
 *      such as the author of the report, the id of the reported post and the reason for the report.
 *  Typical Element:
 *      The typical element of an ReportPost is a report with its meta-information, such as:
 *          - its unique identifier
 *          - its author
 *          - the reported id
 *          - its text content, which is the reason for the report
 *          - the timestamp at which it was created.
 */
public class ReportPost extends AbstractPost implements Post {
    /**
     * AF(c) = < id, author, reportedId, contents, timestamp > 
     *      where:
     *          - id represents the unique id of the report c,
     *          - author represents the author of the report c,
     *          - reportedId represents the id of the report c,
     *          - contents represents the contents of the report c,
     *          - timestamp is the timestamp at which c was created.
     */
    /**
     * RI :     author != null && contents != null 
     *      && postType != null && postType == PostType.REPORT
     *      &&  0 < contents.length() <= Post.MAX_POST_LENGTH
     *      &&  timestamp != null
     */
    private int reportedId;

    /**
     * @requires:   author != null && reportContents != null && timestamp != null && 0 < reportContents.length() <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException is thrown if author or reportContents is null,
     *              TextTooLongException is thrown if reportContents.length() exceeds Post.MAX_POST_LENGTH,
     *              EmptyTextException is thrown if reportContents is empty
     * @effects:    creates a new post with the given id, author, the id of the reported post,
     *              the content of the report and the given timestamp
     */
    public ReportPost(int id, String author, int reportedPostId, String reportContent, LocalDateTime timestamp) throws NullPointerException, TextTooLongException, EmptyTextException {
        if (author == null || reportContent == null)
            throw new NullPointerException("author and contents of the post must not be null.");
        if (timestamp == null)
            throw new NullPointerException("timestamp must not be null");
        if (reportContent.isEmpty())
            throw new EmptyTextException("the text of a post must not be empty");
        if (reportContent.length() > Post.MAX_POST_LENGTH)
            throw new TextTooLongException("the text of a post cannot exceed " + Post.MAX_POST_LENGTH + " characters.");
    
        this.postType = PostType.REPORT;
        this.id = id;
        this.author = author;
        this.reportedId = reportedPostId;
        this.contents = reportContent;
        this.timestamp = LocalDateTime.now();
        this.contentDescriptor = "Report";
    }

    /**
     * @requires:   author != null && reportContents != null && 0 < reportContents.length() <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException is thrown if author or reportContents is null,
     *              TextTooLongException is thrown if reportContents.length() exceeds Post.MAX_POST_LENGTH,
     *              EmptyTextException is thrown if reportContents is empty
     * @effects:    creates a new post with a new unique id, the given author, the id of the reported post,
     *              the content of the report and this moment's timestamp
     */
    public ReportPost(int id, String author, int reportedPostId, String reportContent) throws NullPointerException, TextTooLongException, EmptyTextException{
        this(id, author, reportedPostId, reportContent, LocalDateTime.now());
    }

    /**
     * @effects: returns the id of the reported post.
     */
    public int getReportedId(){
        return reportedId;
    }

    // Specification given by the interface Post.
    public String getContents(){
        return "Reported id: " + reportedId + ".\n"
                + "Report content: " + contents;
    }

    public String toString(){
        return "{ Post identified by: " + getId() + ".\n" +
                "\tType: " + getPostType() + ".\n" + 
                "\tAuthor: " + getAuthor() + ".\n" +
                "\tTimestamp: " + getTimestamp().format(getTimeFormat()) + ".\n" +
                "\t" + contentDescriptor + 
                ":\n\t\t- Reported id: " + reportedId + 
                ".\n\t\t- Report content: " + contents + " }\n";
    }
}

