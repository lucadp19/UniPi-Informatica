package microblog.tests;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import microblog.*;
import microblog.posts.*;
import microblog.exceptions.*;

public class TestSN {
    public static void main(String[] args) {
        SocialNetwork sn = new SocialNetworkImpl();

        populateSocialNetwork(sn);
        testUserSignUp(sn);
        testPostCreation(sn);
        testLikeCreation(sn);

        System.out.println("\n*** Influencers. ***");
        System.out.println(sn.influencers() + "\n");

        testMentionedUsers(sn);
        testWrittenBy(sn);
        testContaining(sn);
        testGuessFollowers(sn);
        testGetPostFromId(sn);
    }

    public static void testGetPostFromId(SocialNetwork sn){
        System.out.println("\n*** Testing getPostFromId. ***");

        System.out.println("-- Null list.");
        try {
            sn.getPostFromId(null, 15);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing null.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(100, "Uno", "Test"));
            list.add(null);
            sn.getPostFromId(list, 25);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- No post has the given id.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(200, "Uno", "Test"));
            list.add(new TextPost(201, "Due", "Test"));
            list.add(new TextPost(202, "Tre", "Test"));
            list.add(new TextPost(203, "Uno", "Test"));
            System.out.println(sn.getPostFromId(list, 204));
        } catch (IdNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Correct example.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(200, "Uno", "Test"));
            list.add(new TextPost(201, "Due", "Test"));
            list.add(new TextPost(202, "Tre", "Test"));
            list.add(new TextPost(203, "Uno", "Test"));
            System.out.println(sn.getPostFromId(list, 202));
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }
    }

    public static void testGuessFollowers(SocialNetwork sn){
        System.out.println("\n*** Testing guessFollowers. ***");

        System.out.println("-- Null list.");
        try {
            sn.guessFollowers(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing null.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(100, "Uno", "Test"));
            list.add(null);
            sn.guessFollowers(list);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing likes to non-existing posts.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(100, "Uno", "Test"));
            list.add(new LikePost(101, "Due", 1000));
            sn.guessFollowers(list);
        } catch (IdNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing self-likes.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(100, "Uno", "Test"));
            list.add(new LikePost(101, "Uno", 100));
            sn.guessFollowers(list);
        } catch (IllegalLikeException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Correct example.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(101, "Uno", "Test"));
            list.add(new TextPost(102, "Due", "Altro test"));
            list.add(new LikePost(103, "Uno", 102));
            list.add(new TextPost(104, "Quattro", "Ultimo test"));
            list.add(new LikePost(105, "Quattro", 101));
            list.add(new LikePost(106, "Tre", 101));
            System.out.println("\"Uno\" should follow \"Due\", \"Tre\" and \"Quattro\" should follow \"Uno\".");
            System.out.println(sn.guessFollowers(list));
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }
    }

    public static void testContaining(SocialNetwork sn){
        System.out.println("\n*** Testing containing. ***");
        System.out.println("-- Null list.");
        try {
            sn.containing(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing null values.");
        try {
            List<String> list = new ArrayList<>();
            list.add(null);
            list.add("ciao");
            sn.containing(list);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }


        System.out.println("-- Post containing \"ciao\" or \"Menzioni\".");
        try{
            List<String> list = new ArrayList<>();
            list.add("ciao");
            list.add("Menzioni");
            System.out.println(sn.containing(list));
        } catch (Throwable e){
            System.out.println("Shouldn't have caught this exception:");
            System.out.println(e);
        }

        System.out.println("-- Post containing \"calzolaio\": should return an empty list");
        try {
            List<String> list = new ArrayList<>();
            list.add("calzolaio");
            System.out.println(sn.containing(list));
        }  catch (Throwable e){
            System.out.println("Shouldn't have caught this exception:");
            System.out.println(e);
        }

    }

    public static void testWrittenBy(SocialNetwork sn){
        System.out.println("*** Posts written by \"Uno\" in the social network.");
        try {
            System.out.println(sn.writtenBy("Uno") + "\n");
        } catch (Throwable e) {
            System.out.println("Shouldn't have catched this exception:");
            System.out.println(e);
        }

        System.out.println("*** Testing writtenBy with one parameter. ***");
        System.out.println("-- Null author.");
        try {
            sn.writtenBy(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Author not signed up.");
        try {
            sn.writtenBy("NonUtente");
        } catch (UserNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("\n*** Testing writtenBy with two parameters. ***");
        System.out.println("-- Null list.");
        try {
            sn.writtenBy(null, "Uno");
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing null values.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(null);
            list.add(new TextPost(20, "Uno", "Test"));
            sn.writtenBy(list, "Uno");
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        List<Post> list = new ArrayList<>();
        try {
            list.add(new TextPost(21, "Uno", "Test"));
            list.add(new TextPost(22, "Due", "TestB"));
            list.add(new TextPost(23, "Cinque", "TestC"));
            list.add(new LikePost(24, "Uno", 3));
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception:");
            System.out.println(e);
        }

        System.out.println("-- Null author.");
        try {
            sn.writtenBy(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Author not signed up.");
        try {
            sn.writtenBy(list, "NonUtente");
        } catch (UserNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }        

        System.out.println("-- Correct list and user parameters.");
        try {
            System.out.println(sn.writtenBy(list, "Uno"));
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }    
    }

    public static void testMentionedUsers(SocialNetwork sn){
        System.out.println("*** Mentioned users in the social network. ***");
        System.out.println(sn.getMentionedUsers().toString() + "\n");

        System.out.println("*** Mentioned users from a list. ***");
        System.out.println("-- Null list.");
        try {
            sn.getMentionedUsers(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- List containing null values.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(null);
            list.add(new TextPost(8, "Uno", "Test"));
            sn.getMentionedUsers(list);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Correct list.");
        try {
            List<Post> list = new ArrayList<>();
            list.add(new TextPost(7, "Due", "@Uno @Settanta"));
            list.add(new TextPost(15, "Uno", "Testing @@"));
            list.add(new TextPost(19, "Tre", "a@a"));
            list.add(new TextPost(22, "Uno", "@Due"));
            System.out.println("Should contain only Uno and Due: " + sn.getMentionedUsers(list));
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("");
    }

    public static void populateSocialNetwork(SocialNetwork sn){
        System.out.println("*** Populating the social network. ***");
        try {
            sn.signUp("Uno");
            sn.signUp("Due");
            sn.signUp("Tre");
            sn.signUp("Quattro");
            sn.signUp("Uno_1");
            System.out.println("\tUsers signed up correctly.");
        } catch (Throwable e){
            System.out.println("Shouldn't have caught this exception:");
            System.out.println(e);
        }

        try {
            int firstPost = sn.submitPost("Uno", "Primo messaggio");
            int secondPost = sn.submitPost("Due", "Secondo messaggio, ciao @Uno");
            int thirdPost = sn.addLike("Uno", secondPost);
            int fourthPost = sn.addLike("Tre", secondPost);
            int fifthPost = sn.submitPost("Quattro", "Menzioni a @Uno @Due e @Cinque");
            int sixthPost = sn.addLike("Uno_1", fifthPost);
            int seventhPost = sn.submitPost("Tre", "ciao a tutti", LocalDateTime.of(2020, 11, 20, 11, 00));
            System.out.println("\tPosts/likes submitted correctly.");
        } catch (Throwable e){
            System.out.println("Shouldn't have caught this exception:");
            System.out.println(e);
        }

        System.out.println("-- Printing set of users.");
        System.out.println(sn.getUserSet());

        System.out.println("-- Printing set of posts.");
        System.out.println(sn.getPostSet());

        System.out.println("");
    }

    public static void testLikeCreation(SocialNetwork sn){
        System.out.println("*** Testing likes. ***");
        System.out.println("-- Null author.");
        try {
            sn.addLike(null, 2);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Null timestamp.");
        try {
            sn.addLike("Due", 2, null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- User not found.");
        try {
            sn.addLike("Cinque", 2);
        } catch (UserNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Id not found.");
        try {
            sn.addLike("Uno", 25000);
        } catch (IdNotFoundException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Users liking their own post.");
        try {
            // post with id 0 is made by Uno
            sn.addLike("Uno", 0);
        } catch (IllegalLikeException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("-- Users liking a post they already liked.");
        try {
            sn.addLike("Uno", 1);
            sn.addLike("Uno", 1);
        } catch (IllegalLikeException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }
    }

    private static void testPostCreation(SocialNetwork sn){
        System.out.println("*** Testing post creation. ***");
        try {
            System.out.println("-- Null author.");
            sn.submitPost(null, "Null");
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Null text.");
            sn.submitPost("Uno", null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Null timestamp.");
            sn.submitPost("Uno", "A", null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Empty text.");
            sn.submitPost("Uno", "");
        } catch (EmptyTextException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Text too long.");
            sn.submitPost("Uno", "a".repeat(141));
        } catch (TextTooLongException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Author not in the social network.");
            sn.submitPost("Cinque", "a");
        } catch (UserNotFoundException e){
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("");
    }

    private static void testUserSignUp(SocialNetwork sn){
        System.out.println("*** Testing sign-up. ***");

        try {
            System.out.println("-- Null username.");
            sn.signUp(null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Already existing user.");
            sn.signUp("Uno");
        } catch (UserAlreadyExistsException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Illegal username because of spaces.");
            sn.signUp("A b");
        } catch (IllegalUsernameException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Illegal username because of non-alphanumeric/underscore characters.");
            sn.signUp("A23!!b");
        } catch (IllegalUsernameException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("");
    }
}
