package microblog;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

import microblog.posts.*;
import microblog.exceptions.*;
import microblog.datastructs.StringIntegerPair;
import microblog.datastructs.PostType;

/**
 * Overview:
 *      A SocialNetworkImpl is an implementation of the mutable datatype SocialNetwork,
 *      used to represent the inner workings of a social network. 
 *      The SocialNetworkImpl datatype makes several useful features available to someone who 
 *      wants to simulate a social network or wants to do data analysis. 
 *      Some of those features are
 *          - sign-up users with uniques usernames,
 *          - submit posts or like other posts,
 *          - get informations on several aspects of the social network.
 * Typical Element:
 *      A SocialNetworkImpl is typically made by:
 *          - a set of signed-up users
 *          - a set of posts (which can be textual, likes, or other types)
 *          - a map linking users with users they follow,  
 *              where "A follows B" means that A has liked at least one post made by B,
 *          - a map linking posts with users whom liked the given post.
 */
public class SocialNetworkImpl implements SocialNetwork {
    /**
     * AF(c) = < following, postToLikes >
     *      where following, postToLikes are two functions such that
     *      - following : Users -> Set(Users) 
     *          following(u) = { u' | u' has liked at least one post by u }
     *      - postToLikes : Post -> Set(Users)
     *          postToLikes(p) = { u | u has liked  p }
     */
    /**
     * RI :     following != null 
     *       && postToLikes != null
     *       && idGenerator >= 0
     *       && (forall u: u in following.keySet() => following.get(u) != null)                                 // the sets of following users are not null
     *       && (forall u: u in following.keySet() => (forall u': u' in following.get(u) => u' != null))        // every user in the set of following users is not null 
     *       && (forall p: p in postToLikes.keySet() => postToLikes.get(p) != null)                             // the sets of liking users are not null
     *       && (forall p: p in postToLikes.keySet() => (forall u: u in postToLikes.get(p) => u != null))       // every user in the set of liking users is not null
     *       && (forall u: u in following.keySet() => !following.get(u).contains(u))                            // users cannot follow themselves
     *       && (forall u: u in following.keySet() => u only contains letters, numbers and underscores)         // usernames must contain only letters, numbers and underscores 
     *       && (forall p, p': p, p' in following.keySet() && p != p' => p.getId() != p'.getId())               // different posts have different identifiers
     *       && (forall p: p in postToLikes.keySet() => p.author in following.keySet())                         // users who have posted something must be signed up
     *       && (forall p: p in postToLikes.keySet() => (forall u: u in postToLikes.get(p) => u != p.author))   // users cannot like their own posts
     *       && (forall p: p in postToLikes.keySet() => 
     *                  (forall u: u in postToLikes.get(p) => p.author in following.get(u)))                    // users who like a post must follow the author of the post
     *       && (forall u, u': u, u' in following.keySet() and                                                  // if u' does not like any post from u, then u' does not follow u
     *                  (forall p: p in postToLikes.get(p) and p.author = u => !postToLikes.get(p).contains(u')) 
     *              => !following.get(u').contains(u))
     */


    protected AtomicInteger idGenerator = new AtomicInteger(0);
    protected final Map<String, Set<String>> following;
    protected final Map<Post, Set<String>> postToLikes;

    /**
     * @effects: creates a new empty SocialNetwork.
     */
    public SocialNetworkImpl(){
        following = new HashMap<String, Set<String>>();
        postToLikes = new HashMap<Post, Set<String>>();

        // checking RepInv
        assert checkRep();
    }

    // Specification given by the interface SocialNetwork.
    public void signUp(String user) throws NullPointerException, UserAlreadyExistsException, IllegalUsernameException {
        // checking RepInv
        assert checkRep();

        if(user == null)
            throw new NullPointerException("username cannot be null.");
        if(isSignedUp(user))
            throw new UserAlreadyExistsException("user \"" + user + "\" is already signed up.");
        if(!isValidUsername(user))
            throw new IllegalUsernameException("\"" + user + "\" is not a valid username. Usernames must not be empty and they must contain only alphanumeric characters or underscores.");

        following.put(user, new HashSet<String>());

        // checking RepInv
        assert checkRep();
    }

    // Specification given by the interface SocialNetwork.
    public int submitPost(String user, String text, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException {
        // checking RepInv
        assert checkRep();
        
        if (user == null || text == null)
            throw new NullPointerException("user and text must not be null values.");
        if(timestamp == null)
            throw new NullPointerException("timestamp must not be null");
        if (!isSignedUp(user))
            throw new UserNotFoundException("user " + user + " is not signed up in this social network.");
        if(text.isEmpty())
            throw new EmptyTextException("text must not be empty.");
        if(text.length() > Post.MAX_POST_LENGTH)
            throw new TextTooLongException("text must not exceed " + Post.MAX_POST_LENGTH + " characters");
        
        Post p = new TextPost(idGenerator.getAndIncrement(), user, text, timestamp);
        postToLikes.put(p, new HashSet<String>());

        // checking RepInv
        assert checkRep();

        // returning the id of the post
        return p.getId();
    }

    // Specification given by the interface SocialNetwork.
    public int submitPost(String user, String text) throws NullPointerException, UserNotFoundException, EmptyTextException, TextTooLongException {
        return submitPost(user, text, LocalDateTime.now());
    }

    // Specification given by the interface SocialNetwork.
    public int addLike(String user, int postId, LocalDateTime timestamp) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException {
        // checking RepInv
        assert checkRep();

        if (user == null)
            throw new NullPointerException("user must not be null.");
        if (timestamp == null)
            throw new NullPointerException("timestamp must not be null.");
        if (!isSignedUp(user))
            throw new UserNotFoundException("user " + user + " is not signed up in this social network.");
        
        // getPostFromId automatically throws IdNotFoundException if postId doesn't identify any post in this
        Post postToLike = getPostFromId(postId);

        if (postToLike.getAuthor() == user)
            throw new IllegalLikeException("user " + user + " cannot like their own post.");
        
        // Try to add user to the set of likes.
        // If user had already liked the post an exception will be thrown
        if(!postToLikes.get(postToLike).add(user)){
            throw new IllegalLikeException("user " + user + " had already liked the post " + postId + ".");
        }

        // user now follows the author of the liked post
        following.get(user).add(postToLike.getAuthor());
        Post like = new LikePost(idGenerator.getAndIncrement(), user, postId, timestamp);
        postToLikes.put(like, new HashSet<>());
        
        // checking RepInv
        assert checkRep();

        return like.getId();
    }

    // Specification given by the interface SocialNetwork.
    public int addLike(String user, int postId) throws NullPointerException, UserNotFoundException, IdNotFoundException, IllegalLikeException {
        return addLike(user, postId, LocalDateTime.now());
    }

    // Specification given in the interface SocialNetwork.
    public Map<String, Set<String>> guessFollowers(List<Post> ps) throws NullPointerException, IdNotFoundException, IllegalLikeException {
        // checking RepInv
        assert checkRep();

        if (ps == null)
            throw new NullPointerException("the list of posts must not be null.");

        Map<String, Set<String>> newSocialMap = new HashMap<String, Set<String>>();
        // Populating the users of this new social map
        for (Post p : ps) {
            if (p == null)
                throw new NullPointerException("each post in the list of posts must not be null.");

            if (!newSocialMap.keySet().contains(p.getAuthor()))
                newSocialMap.put(p.getAuthor(), new HashSet<>());
        }

        for (Post p : ps) {
            if (p.getPostType() == PostType.LIKE){
                Post likedPost;
                int likedId = Integer.parseInt(p.getContents());

                try {
                    likedPost = getPostFromId(ps, likedId); 
                } catch (IdNotFoundException e) {
                    throw new IdNotFoundException("identifier " + likedId + " does not identify any post in the list of posts.");
                }
                // if the like refers to a post by the same author throw exception
                if (likedPost.getAuthor() == p.getAuthor())
                    throw new IllegalLikeException("a user cannot like his own posts.");

                // the author of the like follows the author of the liked post
                newSocialMap.get(p.getAuthor()).add(likedPost.getAuthor());
            }
        }

        // checking RepInv
        assert checkRep();

        return newSocialMap;
    }

    
    // Specification given by the interface SocialNetwork.
    public List<String> influencers() {
        // checking RepInv
        assert checkRep();

        Map<String, Set<String>> followersMap = getFollowersMap();
        List<StringIntegerPair> pairedList = new ArrayList<>();

        // paired lists is populated with pairs (user, n) where n is the number of followers
        for (Map.Entry<String, Set<String>> entry : followersMap.entrySet()) 
            pairedList.add(new StringIntegerPair(entry.getKey(), entry.getValue().size()));
        
        // pairedList is sorted in reverse order
        Collections.sort(pairedList, Collections.reverseOrder());

        // information from the pairedList is copied in a string list
        List<String> influencersList = new ArrayList<>();
        for (StringIntegerPair pair : pairedList)
            influencersList.add(pair.getString());

        return influencersList;
    }

    // Specification given by the interface SocialNetwork.
    public Set<String> getMentionedUsers(){
        return getMentionedUsers(getPostList());
    }

    // Specification given by the interface SocialNetwork.
    public Set<String> getMentionedUsers(List<Post> ps) throws NullPointerException {
        // checking RepInv
        assert checkRep();

        if(ps == null)
            throw new NullPointerException("the list of posts ps cannot be null.");

        Set<String> mentions = new HashSet<String>();
        for (Post p : ps) {
            if (p == null)
                throw new NullPointerException("posts in the list of posts must not be null.");
            mentions.addAll(getTagsFromPost(p));
        }

        return mentions;
    }

    // Specification given by the interface SocialNetwork.
    public List<Post> writtenBy(String username) throws NullPointerException, UserNotFoundException {
        // checking RepInv
        assert checkRep();

        if (username == null)
            throw new NullPointerException("username cannot be null.");
        if (!isSignedUp(username))
            throw new UserNotFoundException("user " + username + " is not signed up in this social network.");
        
        return writtenBy(getPostList(), username);
    }

    // Specification given by the interface SocialNetwork.
    public List<Post> writtenBy(List<Post> ps, String username) throws NullPointerException, UserNotFoundException {
        // checking RepInv
        assert checkRep();
        
        if (ps == null || username == null)
            throw new NullPointerException("post list and username must not be null values.");
        if (!isSignedUp(username))
            throw new UserNotFoundException("user " + username + " is not signed up in this social network.");

        List<Post> postsWrittenBy = new ArrayList<Post>();
        for(Post p : ps) {
            if (p == null)
                throw new NullPointerException("elements of post list must not be null values.");
            if (p.getAuthor() == username) {
                postsWrittenBy.add(p);
            }
        }

        return postsWrittenBy;
    }

    // Specification given by the interface SocialNetwork.
    public List<Post> containing(List<String> words) throws NullPointerException {
        // checking RepInv
        assert checkRep();

        if (words == null)
            throw new NullPointerException("list of words cannot be null.");
        for (String w : words) {
            if (w == null)
                throw new NullPointerException("every word in the list of words must not be null.");
        }

        List<Post> ps = new ArrayList<Post>();
        for (Post p : getPostSet()){
            for (String w : words) {
                if (p.getContents().contains(w)) {
                    ps.add(p);
                    break;
                }
            }
        }
        return ps;
    }

    // Specification given in the interface SocialNetwork.
    public Post getPostFromId(List<Post> postList, int postId) throws NullPointerException, IdNotFoundException {
        // checking RepInv
        assert checkRep();

        if (postList == null)
            throw new NullPointerException("postList must not be null.");
        Post postToFind = null;

        for(Post p : postList){
            if(p == null)
                throw new NullPointerException("every post in postList must not be null.");

            if(p.getId() == postId){
                postToFind = p;
                break;
            }
        }

        if (postToFind == null)
            throw new IdNotFoundException("identifier " + postId + " does not identify any post in postList.");
        
        return postToFind;
    }

    /**
     * @effects: returns a set with all the users signed up in this
     */
    public Set<String> getUserSet(){
        return new HashSet<>(following.keySet());
    }

    /**
     * @effects: returns a list with all the users signed up in this
     */
    public List<String> getUserList(){
        return new ArrayList<String>(following.keySet());
    }

    /**
     * @effects: returns a set with all the posts in this
     */
    public Set<Post> getPostSet(){
        return new HashSet<>(postToLikes.keySet());
    }

    /**
     * @effects: returns a list with all the posts in this
     */
    public List<Post> getPostList(){
        return new ArrayList<Post>(postToLikes.keySet());
    }
    
    /**
     * @requires:   p != null
     * @throws:     NullPointerException is thrown if p == null
     * @effects:    returns a set containing every mention in p, where a
     *              mention is a pattern such as "@name" with the additional condition
     *              that "name" is a user signed up in this
     */
    protected Set<String> getTagsFromPost(Post p) throws NullPointerException {
        if (p == null)
            throw new NullPointerException("post cannot be null.");
    
        Set<String> mentions = new HashSet<String>();
        // pattern for a single (non empty) word beginning with "@" and containing only letters, numbers or underscores
        Pattern pattern = Pattern.compile("\\B@\\w+");
        Matcher matcher = pattern.matcher(p.getContents());

        while(matcher.find()){
            String user = matcher.group().substring(1);
            if(isSignedUp(user))
                mentions.add(user);
        }
        return mentions;
    }

    /**
     * @effects: returns true if and only if username is a valid username: 
     *           username is not empty and contains only alphanumeric characters and/or underscores
     */
    protected boolean isValidUsername(String username){
        return username.matches("[a-zA-Z0-9_]+");
    }

    /**
     * @effects: returns true if and only if username is a user signed up in this
     */
    protected boolean isSignedUp(String username){
        return getUserSet().contains(username);
    }

    /**
     * @requires:   postId is the identifier of a post in this
     * @throws:     IdNotFoundException is thrown if postId does not identify any post in this
     * @effects:    returns the post identified by postId.
     */
    protected Post getPostFromId(int postId) throws IdNotFoundException {
        Post post;

        try { 
            post = getPostFromId(getPostList(), postId);
        } catch (IdNotFoundException e) {
            throw new IdNotFoundException("identifier " + postId + " does not identify any post in this social network.");
        }
        
        return post;
    }

    /**
     * @effects: returns a map between users and users who follow them
     */
    protected Map<String, Set<String>> getFollowersMap(){
        Map<String, Set<String>> followersMap = new HashMap<>();
        List<String> userList = getUserList();

        // initialize the map
        for (String user : userList)
            followersMap.put(user, new HashSet<>());

        for (String user : userList)
            // if "user" follows "followed"
            for (String followed : following.get(user))
                // then "followed" is followed by "user"
                followersMap.get(followed).add(user);
        
        return followersMap;
    }

    /**
     * @effects: returns true if the RepInv is satisfied, false otherwise
     */
    protected boolean checkRep() {
        if(following == null || postToLikes == null)
            return false;
        
        for (String u : following.keySet()){
            // users cannot be null
            if (u == null)
                return false;

            // following set cannot be null
            if (following.get(u) == null)
                return false;
            
            // users cannot follow themselves
            if(following.get(u).contains(u))
                return false;

            // usernames must be valid
            if(!isValidUsername(u))
                return false;

            // following users cannot be null
            for (String v : following.get(u))
                if (v == null)
                    return false;
        }
            
        
        for (Post p : postToLikes.keySet()) {
            // posts cannot be null
            if (p == null)
                return false;
            
            // set of likes cannot be null
            if (postToLikes.get(p) == null)
                return false; 
            
            // users who like p cannot be null
            for (String u : postToLikes.get(p))
                if (u == null)
                    return false;
            
            // author must be signed up
            if (!following.keySet().contains(p.getAuthor()))
                return false;
            
            // author of post p cannot like post p
            if (postToLikes.get(p).contains(p.getAuthor()))
                return false;
            
            // if u likes p then u follows the author of p
            for (String u : postToLikes.get(p))
                if(!following.get(u).contains(p.getAuthor()))
                    return false;
            
            // different posts must have different ids
            for (Post p1 : postToLikes.keySet())
                if(!p1.equals(p) && p.getId() == p1.getId())
                    return false;
        }

        // if v doesn't like any post by u then v cannot follow u
        for (String u : following.keySet()){
            for (String v : following.keySet()){
                boolean likesAtLeastOne = false;

                // already checked that users can't follow themselves
                if (v.equals(u)) continue;

                for (Post p : postToLikes.keySet()) {
                    if (p.getAuthor().equals(u) && postToLikes.get(p).contains(v)) {
                        likesAtLeastOne = true;
                        break;
                    }
                }
                
                if (likesAtLeastOne && !following.get(v).contains(u))
                    return false;
            }
        }
        
        // every check has been made
        return true;
    }
}