package microblog;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import microblog.exceptions.*;
import microblog.posts.*;

/**
 * Overview:
 *      A SocialNetworkReport is an extension of the mutable datatype SocialNetworkImpl
 *      used to represent the inner workings of a social network, with the additional 
 *      possibility of reporting posts made by users.
 *      The SocialNetworkReport datatype makes several useful features available to someone who 
 *      wants to simulate a social network or wants to do data analysis. 
 *      Some of those features are
 *          - sign-up users with uniques usernames,
 *          - submit posts or like other posts,
 *          - get informations on several aspects of the social network,
 *          - reporting a post made by a user,
 *          - getting information about the reported posts.
 * Typical Element:
 *      A SocialNetworkReport is typically made by:
 *          - a set of signed-up users
 *          - a set of posts (which can be textual, likes, or other types)
 *          - a map linking users with users they follow,  
 *              where "A follows B" means that A has liked at least one post made by B,
 *          - a map linking posts with users whom liked the given post,
 *          - a map linking posts with reports regarding the given post.
 */
public class SocialNetworkReport extends SocialNetworkImpl {
    /**
     * AF(c) = < following, postToLikes, reports > 
     *      where following, postToLikes are the same functions as the ones in SocialNetworkImpl,
     *      whereas reports is a function
     *          reports : Posts -> Set(Reports)
     *          reports(p) = { r | r is a report regarding the post p }.
     */
    /**
     * RI :    SocialNetworkImpl_RI 
     *      && reports != null
     *      && forall p : p in postsToLikes.keySet() => p in reports.keySet()                       // every public post must be reportable
     *      && forall p : p in reports.keySet() => (forall r : r in reports.get(p) => r != null)    // every report must not be null
     *      && forall p : p in reports.keySet() =>                                                  // given a post p, a report in reports.get(p) must refer to post p
     *              (forall r : r in reports.get(p) => r.getReportedId() == p.getId())
     */
    
    // the map linking posts and reports
    private Map<Post, Set<ReportPost>> reports;

    /**
     * @effects: creates a new empty SocialNetworkReport
     */
    public SocialNetworkReport(){
        super();
        reports = new HashMap<>();

        // checking RepInv
        assert checkRepReport();
    }

    /**
     * @requires:   given by the interface SocialNetwork.
     * @throws:     given by the interface SocialNetwork.
     * @modifies:   this
     * @effects:    same as the ones given in the interface SocialNetwork,
     *              but it also adds the new post to the set of posts that can be reported.
     */
    public int submitPost(String user, String text, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException {
        // checking RepInv
        assert checkRepReport();
        
        // The call to super's submitPost adds a post only if the preconditions are satisfied.
        // Otherwise it throws an exception, and it's propagated to the first caller by this method.
        int newPostId = super.submitPost(user, text, timestamp);

        try { 
            addToReportablePosts(newPostId);
        } catch (IdNotFoundException e){
            // This exception will never be caught because the new post has been inserted in the set of posts.
            throw new IllegalStateException("An error occurred while creating the post.");
        }

        // check RepInv
        assert checkRepReport();

        // returning the id of the post
        return newPostId;
    }

     /**
     * @requires:   given by the interface SocialNetwork.
     * @throws:     given by the interface SocialNetwork.
     * @modifies:   this
     * @effects:    same as the ones given in the interface SocialNetwork,
     *              but it also adds the new post to the set of posts that can be reported.
     */
    public int submitPost(String user, String text) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException {
        return submitPost(user, text, LocalDateTime.now());
    }

    /**
     * @requires:   given by the interface SocialNetwork.
     * @throws:     given by the interface SocialNetwork.
     * @modifies:   this
     * @effects:    same as the ones given in the interface SocialNetwork,
     *              but it also adds the new post to the set of posts that can be reported.
     */
    public int addLike(String user, int postId, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException {
        // checking RepInv
        assert checkRepReport();
        
        // The call to super's addLike adds a like only if the preconditions are satisfied.
        // Otherwise it throws an exception, which is then propagated to the first caller by this method.
        int likeId = super.addLike(user, postId, timestamp);

        try { 
            addToReportablePosts(likeId);
        } catch (IdNotFoundException e){
            // This exception will never be caught because the new post has been inserted in the set of posts.
            throw new IllegalStateException("An error occurred while creating the post.");
        }

        // checking RepInv
        assert checkRepReport();

        // returning the id of the post
        return likeId;
    }

    /**
     * @requires:   given by the interface SocialNetwork.
     * @throws:     given by the interface SocialNetwork.
     * @modifies:   this
     * @effects:    same as the ones given in the interface SocialNetwork,
     *              but it also adds the new post to the set of posts that can be reported.
     */
    public int addLike(String user, int postId) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException {
        return addLike(user, postId, LocalDateTime.now());
    }

    /**
     * @requires:   user != null && reportText != null && user is a user of this Social Network &&
     *              postId is the identifier of a post in this Social Network &&
     *              0 < reportText.length() < Post.MAX_TEXT_LENGTH
     * @throws:     NullPointerException is thrown if user or reportText are null
     *              UserNotFoundException is thrown if user is not a user of Social Network
     *              IdNotFoundException is thrown if postId does not identify any post in this Social Network
     *              TextTooLongException is thrown if reportText.length() is greater or equal to Post.MAX_TEXT_LENGTH
     *              EmptyTextException is thrown if reportText is the empty text
     * @modifies:   this
     * @effects:    adds a new report (filed by the given user, with regards to the post identified by postId 
     *              and with reason given in reportText) to the Social Network.
     */
    public void reportPost(String user, int postId, String reportText) throws NullPointerException, UserNotFoundException, IdNotFoundException, TextTooLongException, EmptyTextException {
        // checking RepInv
        assert checkRepReport();
        
        if(user == null || reportText == null)
            throw new NullPointerException("user and reportText must not be null");
        if(!isSignedUp(user))
            throw new UserNotFoundException("User " + user + " is not signed up in this social network.");
        if(reportText.isEmpty())
            throw new EmptyTextException("report must not be empty.");
        if(reportText.length() > Post.MAX_POST_LENGTH)
            throw new TextTooLongException("report must not exceed " + Post.MAX_POST_LENGTH + " characters");
        
        // automatically throws IdNotFoundException if postId does not identify any post in this social network
        Post postToReport = getPostFromId(postId);

        // creating the report post
        ReportPost report = new ReportPost(idGenerator.getAndIncrement(), user, postToReport.getId(), reportText);
        reports.get(postToReport).add(report);

        // checking RepInv
        assert checkRepReport();
    }

    /**
     * @effects: returns a map that has 
     *              - posts with at least one report as keys
     *              - a set of the reports regarding the given post as value
     */
    public Map<Post, Set<ReportPost>> reportedPosts(){
        // checking RepInv
        assert checkRepReport();

        Map<Post, Set<ReportPost>> reportedPs = new HashMap<>();
        for(Post post : getPostList()){
            // if a post has been reported at least once, it is included in the map of reported posts
            if (!reports.get(post).isEmpty())
                reportedPs.put(post, new HashSet<>(reports.get(post)));
        }

        // checking RepInv
        assert checkRepReport();

        return reportedPs;
    }

    /**
     * @effects: returns a list of all the reports filed in this social network
     */
    public List<ReportPost> getReportList(){
        // checking RepInv
        assert checkRep();

        List<ReportPost> reps = new ArrayList<>();

        for(Post p : reports.keySet()){
            reps.addAll(reports.get(p));
        }

        return reps;
    }

    /**
     * @requires:   newPostId is the id of a post already in the SocialNetwork
     * @throws:     IdNotFoundException is thrown if newPostId does not identify any post in the social network
     * @modifies:   this
     * @effects:    adds the post identified by newPostId to the list of reportable posts
     */
    private void addToReportablePosts(int newPostId) throws IdNotFoundException {
        Post newPost;    

        try { 
            newPost = getPostFromId(newPostId);
        } catch (IdNotFoundException e) {
            throw new IdNotFoundException("identifier " + newPostId + " does not identify any post in this social network.");
        }
        
        reports.put(newPost, new HashSet<>());
    }

    /**
     * @effects: returns true if the RepInv is satisfied, false otherwise
     */
    protected boolean checkRepReport(){
        // checking RepInv of superclass
        if(!super.checkRep())
            return false;

        // reports map must not be null
        if(reports == null)
            return false;

        // every post must be reportable
        for (Post p : postToLikes.keySet()){
            if (!reports.keySet().contains(p))
                return false;
        }
        
        for(Post p : reports.keySet()){
            // reportable posts must not be null
            if (p == null)
                return false;

            for (ReportPost r : reports.get(p)){
                // reports must not be null
                if (r == null)
                    return false;
                
                // every report in reports.get(p) must be a report of post p
                if (r.getReportedId() != p.getId())
                    return false;
            }
        }

        return true;
    }
}
