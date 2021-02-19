/**
 * A MyIndexedBook is a book with an author, title, publisher, year of publication and genre.
 * It also has a index.
 */
public class MyIndexedBook extends MyBook implements IndexedBook{
    private int index;
    private String genre;

    // @effects: creates a new indexed book with given author, title, publisher, index and genre
    public MyIndexedBook(String author, String title, String publisher, int year, int index, String genre){
        super(author, title, publisher, year);
        this.index = index;
        this.genre = genre;
    }

    // @effects: creates a new indexed book given a book, a genre and an index
    public MyIndexedBook(Book bk, int index, String genre){
        this(bk.getAuthor(), bk.getTitle(), bk.getPublisher(), bk.getYear(), index, genre);
    }

    // @returns: the index of the book
    public int getIndex(){
        return index;
    }

    // @returns: the genre of the book
    public String getGenre(){
        return genre;
    }

    // @returns: true if and only if this and b are in the same genre
    // @throws: NullPointerException if b is null
    public boolean sameGenre(IndexedBook b){
        if (b == null) {
            throw new NullPointerException();
        }

        return this.genre.equals(b.getGenre());
    }
}
