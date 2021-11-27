package microblog.tests;

import java.util.ArrayList;
import java.util.List;

import microblog.*;
import microblog.exceptions.*;
import microblog.posts.*;

public class TestReport {
    public static void main(String[] args) {
        SocialNetworkReport sn = new SocialNetworkReport();
        
        populateSocialNetwork(sn);
        testReports(sn);

        System.out.println("-- Reported posts: ");
        System.out.println(sn.reportedPosts());

        System.out.println("\n-- Report list:");
        System.out.println(sn.getReportList());
    }

    public static void testReports(SocialNetworkReport sn){
        System.out.println("*** Testing reports. ***");
        try {
            System.out.println("-- Null author.");
            sn.reportPost(null, 2, "Null");
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Null text.");
            sn.reportPost("Uno", 2, null);
        } catch (NullPointerException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Empty text.");
            sn.reportPost("Uno", 2, "");
        } catch (EmptyTextException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Text too long.");
            sn.reportPost("Uno", 2, "a".repeat(141));
        } catch (TextTooLongException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Author not in the social network.");
            sn.reportPost("Cinque", 2, "a");
        } catch (UserNotFoundException e){
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        try {
            System.out.println("-- Id not found.");
            sn.reportPost("Uno", 2500, "a");
        } catch (IdNotFoundException e){
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Shouldn't have caught this exception.");
            System.out.println(e);
        }

        System.out.println("");
    }

    public static void populateSocialNetwork(SocialNetworkReport sn){
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
            int seventhPost = sn.submitPost("Tre", "ciao a tutti");
            System.out.println("\tSubmitted likes/posts.");
            sn.reportPost("Uno", fifthPost, "Volevo segnalare Quattro");
            sn.reportPost("Due", fifthPost, "Volevo segnalare Quattro");
            sn.reportPost("Tre", fifthPost, "Volevo segnalare Quattro");
            sn.reportPost("Quattro", thirdPost, "Volevo segnalare Uno");
            System.out.println("\tReports submitted correctly.");
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
}
