package microblog;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.Set;

import microblog.exceptions.*;
import microblog.posts.*;

/**
 * Overview:
 *      A SocialNetwork is a mutable data structure used to represent the inner workings
 *      of a social network. The SocialNetwork datatype makes several useful features available
 *      to someone who wants to simulate a social network or wants to do data analysis: some of 
 *      those features are
 *          - sign-up users with uniques usernames,
 *          - submit posts or like other posts,
 *          - get informations on several aspects of the social network.
 * Typical Element:
 *      A SocialNetwork is typically made by:
 *          - a set of signed-up users
 *          - a set of posts (which can be textual, likes, or other types)
 *          - a map linking users with users they follow,  
 *              where "A follows B" means that A has liked at least one post made by B,
 *          - a map linking posts with users whom liked the given post.
 */
public interface SocialNetwork {

    /**
     * @requires:   user != null, user isn't already signed up in the social network
     *              and user contains only alphanumeric characters and "_"
     * @throws:     NullPointerException is thrown if user == null
     *              UserAlreadyExistsException is thrown if user is already signed up in the social network
     *              IllegalUsernameException is thrown if user contains non-alphanumeric, non-underscore characters
     * @modifies:   this
     * @effects:    user is signed up in the social network
     */
    public void signUp(String user) throws NullPointerException, UserAlreadyExistsException, IllegalUsernameException;

    /**
     * @requires:   user != null, text != null, 0 < text.length <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException if either user or text is null
     *              UserNotFoundException if user is not already signed up in the SocialNetwork
     *              EmptyTextException if text is empty
     *              TextTooLongException if text.length() is greater than Post.MAX_POST_LENGTH
     * @modifies:   this
     * @effects:    adds to this a new Post from user with the specified text, a unique id and
     *              this moment's timestamp to the list of user's posts. 
     *              Furthermore, it returns the new post's unique identifier.
     */
    public int submitPost(String user, String text) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException;

    /**
     * @requires:   user != null, text != null, timestamp != null, 0 < text.length <= Post.MAX_POST_LENGTH
     * @throws:     NullPointerException if user, text or timestamp is null,
     *              UserNotFoundException if user is not already signed up in the SocialNetwork
     *              EmptyTextException if text is empty
     *              TextTooLongException if text.length() is greater Post.MAX_POST_LENGTH
     * @modifies:   this
     * @effects:    adds to this a new Post from user with the specified text, a unique id and
     *              the given timestamp timestamp to the list of user's posts. 
     *              Furthermore, it returns the new post's unique identifier.
     * @returns:    the unique id of the newly submitted post.
     */
    public int submitPost(String user, String text, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException;

    /**
     * @requires:   user != null, user is already signed up, 
     *              postId is the id of a post contained in this social network,
     *              user is not the author of the post identified by postId
     * @throws:     NullPointerException if user is null,
     *              UserNotFoundException if user is not in the SocialNetwork
     *              IdNotFoundException if postId is not the id of a post contained in this social network
     *              IllegalLikeException if user is the author of the post identified by postId or if user already liked such post
     * @modifies:   this
     * @effects:    adds user to the set of users whom have liked the post identified by postId and adds the like to the social network.
     *              If user hadn't liked a post from the author of the post identified by postId, user now follows the author.
     *              Furthermore, it returns the new like's unique identifier.
     */
    public int addLike(String user, int postId) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException;

    /**
     * @requires:   user != null, timestamp != null, user is already signed up, 
     *              postId is the id of a post contained in this social network,
     *              user is not the author of the post identified by postId
     * @throws:     NullPointerException if either user or timestamp is null,
     *              UserNotFoundException if user is not in the SocialNetwork
     *              IdNotFoundException if postId is not the id of a post contained in this social network
     *              IllegalLikeException if user is the author of the post identified by postId or if user already liked such post
     * @modifies:   this
     * @effects:    adds user to the set of users whom have liked the post identified by postId and adds the like to the social network.
     *              If user hadn't liked a post from the author of the post identified by postId, user now follows the author.
     *              Furthermore, it returns the new like's unique identifier.
     */
    public int addLike(String user, int postId, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException;

    /**
     * @requires:   ps != null, (forall p in ps: p != null),
     *              every like post in ps must refer to a post in ps
     * @throws:     NullPointerException is thrown if ps or a post contained in ps is null
     *              IdNotFoundException is thrown if a like post in ps does not refer to any post in ps
     *              IllegalLikeException is thrown if a like post in ps refers to a post by the same user
     * @returns:    a map between the authors of the posts contained in ps and
     *              the users that liked their posts.
     */
    public Map<String, Set<String>> guessFollowers(List<Post> ps) throws NullPointerException, IdNotFoundException, IllegalLikeException;

    /**
     * @effects:    returns a list containing the names of all the users signed up in this,
     *              sorted by number of followers in decreasing order
     */
    public List<String> influencers();

    /**
     * @effects:    returns a set of all the existing users tagged in the posts contained
     *              in the SocialNetwork.
     */
    public Set<String> getMentionedUsers();

    /**
     * @requires:   ps != null, (forall p in ps: p != null)
     * @throws:     NullPointerException if ps or a post contained in ps is null
     * @effects:    returns a set of all the existing users tagged in the posts 
     *              contained in ps.
     */
    public Set<String> getMentionedUsers(List<Post> ps) throws NullPointerException;

    /**
     * @requires:   username != null, username is in the set of users
     * @throws:     NullPointerException if username is null
     *              UserNotFoundException if username is not in the set of signed up users
     * @effects:    returns a list with all the posts written by username
     */
    public List<Post> writtenBy(String username) throws NullPointerException, UserNotFoundException;

    /**
     * @requires:   ps != null, (forall p in ps: p != null),
     *              username != null, username is in the set of users
     * @throws:     NullPointerException if username, ps or a post in ps is null
     *              UserNotFoundException if username is not in the set of signed up users
     * @effects:    returns a list with all the posts written by username contained in the list ps
     */
    public List<Post> writtenBy(List<Post> ps, String username) throws NullPointerException, UserNotFoundException;

    /**
     * @requires:   words != null, (forall w in words: w != null)
     * @throws:     NullPointerException if words or a word in words is null
     * @effects:    returns a list with all the posts containing at least a word that is in words.
     */
    public List<Post> containing(List<String> words) throws NullPointerException;

    /**
     * @requires:   postList != null, (forall p in postList: p != null)
     *              postId is the identifier of a post in postList
     * @throws:     NullPointerException is thrown if postList or a post in postList is null
     *              IdNotFoundException is thrown if no post in postList has postId as identifier
     * @effects:    returns the post contained in postList identified by postId.
     */
    public Post getPostFromId(List<Post> postList, int postId) throws NullPointerException, IdNotFoundException;

    /**
     * @effects: returns a set with all the users signed up in this
     */
    public Set<String> getUserSet();

    /**
     * @effects: returns a list with all the users signed up in this
     */
    public List<String> getUserList();

    /**
     * @effects: returns a set with all the posts in this
     */
    public Set<Post> getPostSet();

    /**
     * @effects: returns a list with all the posts in this
     */
    public List<Post> getPostList();
}