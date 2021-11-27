package microblog.tests;

import java.util.ArrayList;
import java.util.List;

import java.time.LocalDateTime;
import microblog.exceptions.*;
import microblog.posts.*;

public class TestPost {
    public static void main(String[] args) {
        List<Post> posts = new ArrayList<>();

        // correct posts
        System.out.println("*** Adding six posts without errors. ***");
        try {
            posts.add(new TextPost(1, "Uno", "Hello world! @As @sd63 as@2"));
            System.out.println("\tAdded new post.");
            posts.add(new TextPost(2, "Due", "Altro messaggio con menzione a @Uno"));
            System.out.println("\tAdded new post.");
            posts.add(new TextPost(3, "Uno", "Altro messaggio ancora"));
            System.out.println("\tAdded new post.");
            posts.add(new LikePost(4, "Due", 3));
            System.out.println("\tAdded new like.");
            posts.add(new ReportPost(5, "Tre", 2, "Volevo testare le segnalazioni"));
            System.out.println("\tAdded new report.");
            posts.add(new TextPost(6, "Uno", "Messaggio dal passato", LocalDateTime.of(2020, 11, 20, 11, 00)));
            System.out.println("\tAdded new post.");
        } catch (Throwable e) {
            System.out.println("Something went wrong, shouldn't have caught any exception.");
            System.out.println(e);
        } 

        // Text too long
        System.out.println("\n*** Text too long test. ***");
        try {
            posts.add(new TextPost(100, "Ego", "a".repeat(141)));
            System.out.println("Added new post.");
        } catch (TextTooLongException e){
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Something went wrong, shouldn't have caught this exception:");
            System.out.println(e);
        } 

        // Null pointer to author
        System.out.println("\n*** Null author test. ***");
        try {
            posts.add(new TextPost(101, null, "Text"));
            System.out.println("Added new post.");
        } catch (NullPointerException e){
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Something went wrong, shouldn't have caught this exception:");
            System.out.println(e);
        } 

        // Empty content
        System.out.println("\n*** Empty text test. ***");
        try {
            posts.add(new TextPost(102, "Empty", ""));
        } catch (EmptyTextException e) {
            System.out.println("\tCorrectly catched: \n\t" + e);
        } catch (Throwable e) {
            System.out.println("Something went wrong, shouldn't have caught this exception:");
            System.out.println(e);
        } 

        System.out.println("\n*** Printing posts in list. ***");
        System.out.println(posts);
    }
}
