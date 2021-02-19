/**
 * A MyBook is a book with an author, title, publisher and year of publication.
 */
public class MyBook implements Book {
    private String author;
    private String title;
    private String publisher;
    private int year;

    // @effects: creates a new book with given author, title, publisher and year of publication
    // @throws: NullPointerException when the author, title or publisher are null
    public MyBook(String author, String title, String publisher, int year) {
        if (author == null || title == null || publisher == null){
            throw new NullPointerException();
        }

        this.author = author;
        this.title = title;
        this.publisher = publisher;
        this.year = year;
    }

    // @returns: the author of the book
    public String getAuthor(){
        return author;
    }

    // @returns: the title of the book
    public String getTitle(){
        return title;
    }

    // @returns: the publisher of the book
    public String getPublisher(){
        return publisher;
    }

    // @returns: the year of publication of the book
    public int getYear(){
        return year;
    }

    // @returns: true if and only if this and b have the same author
    // @throws: NullPointerException if b is null
    public boolean sameAuthor(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return author.equals(b.getAuthor());
    }

    // @returns: true if and only if this and b have the same title
    // @throws: NullPointerException if b is null
    public boolean sameTitle(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return title.equals(b.getTitle());
    }

    // @returns: true if and only if this and b have the same publisher
    // @throws: NullPointerException if b is null
    public boolean samePublisher(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return publisher.equals(b.getPublisher());
    }

    // @returns: true if and only if this and b were published in the same year
    // @throws: NullPointerException if b is null
    public boolean sameYear(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return year == b.getYear();
    }

    // @returns: true if and only if this and b are the same book, which is, if and only if they have the same title and author
    // @throws: NullPointerException if b is null
    public boolean sameWork(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return (sameTitle(b) && sameAuthor(b));
    }

    public String toString(){
        return author + " - " + title + " - " + publisher + " - " + year;
    }

    // @returns: true if and only if this and b are exactly the same book, which is if they have the same title, author, publisher and year of publication
    // @throws: NullPointerException if b is null
    public boolean equals(Book b){
        if (b == null)
            throw new NullPointerException();
        
        return (sameWork(b) && samePublisher(b) && sameYear(b));
    }
}