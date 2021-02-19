/**
 * A MyLibrary is a collection of books.
 */
public class MyLibrary implements Library {
    protected class BookNode {
        protected Book bk;
        protected BookNode next;
    
        public BookNode(Book bk){
            this(bk, null);
        }
    
        public BookNode(Book bk, BookNode next){
            if (bk == null) {
                throw new NullPointerException();
            }
    
            this.bk = bk;
            this.next = next;
        }
    }

    protected BookNode list;

    // @effects: creates an empty library
    public MyLibrary(){
        list = null;
    }

    // @effects: creates a library with only the book bk
    // @throws: NullPointerException if bk is null
    public MyLibrary(Book bk){
        if (bk == null)
            throw new NullPointerException();
        list = new BookNode(bk);
    }

    // @effects: creates a library from an array of books
    // @throws: NullPointerException if bks is null or if it contains null references
    public MyLibrary(Book[] bks){
        if (bks == null)
            throw new NullPointerException();
        
        for (int i = 0; i < bks.length; i++){
            if (bks[i] == null)
                throw new NullPointerException();
            
            // creates the list
            if (i == 0)
                list = new BookNode(bks[i]);
            else
                this.insert(bks[i]);
        }
    }

    // @effects: inserts the book bk in the library
    // @throws: NullPointerException if bk is null
    public void insert(Book bk){
        if (bk == null)
            throw new NullPointerException();
        
        BookNode newNode = new BookNode(bk, this.list);
        list = newNode;
    }

    // @effects: removes all occurrences of the book bk in the library
    // @throws: NullPointerException if bk is null
    // @throws: ElementNotFoundException if bk isn't in the library
    public void remove(Book bk) throws ElementNotFoundException {
        if (bk == null)
            throw new NullPointerException();

        BookNode current = this.list;
        BookNode prec = null;
        boolean elementInList = false;
        while(current != null){
            // if current is a reference to the head of the list
            // and the first book has to be removed
            if(prec == null && current.bk.equals(bk)) {
                elementInList = true;
                current = current.next;
            }
            // if the current book has to be removed
            else if (current.bk.equals(bk)) {
                elementInList = true;
                prec.next = current.next;
                current = current.next;
            }
            else {
                prec = current;
                current = current.next;
            }
        }

        if (!elementInList){
            throw new ElementNotFoundException("MyLibrary.remove: element not found in list");
        }
    }

    // @returns: an array of string containing all titles of the books by the author aut contained in the library
    // @throws: NullPointerException if aut is null
    public String[] getByAuthor(String aut){
        if (aut == null)
            throw new NullPointerException();

        int number = getNumberBy("author", aut);
        String[] titles = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getAuthor().equals(aut)) {
                titles[pos] = current.bk.getTitle();
                pos++;
            }
            current = current.next;
        }
        return titles;
    }

    // @returns: an array of string containing all books (in string format) with title tit contained in the library
    // @throws: NullPointerException if tit is null
    public String[] getByTitle(String tit){
        if (tit == null)
            throw new NullPointerException();

        int number = getNumberBy("title", tit);
        String[] books = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getTitle().equals(tit)) {
                books[pos] = current.bk.toString();
                pos++;
            }
            current = current.next;
        }
        return books;
    }

    // @returns: an array of string containing all books (in string format) with publisher pub contained in the library
    // @throws: NullPointerException if pub is null
    public String[] getByPublisher(String pub){
        if (pub == null)
            throw new NullPointerException();

        int number = getNumberBy("publisher", pub);
        String[] books = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getPublisher().equals(pub)) {
                books[pos] = current.bk.toString();
                pos++;
            }
            current = current.next;
        }
        return books;
    }

    // @returns: an array of string containing all books (in string format) published in the year y contained in the library
    // @throws: NullPointerException if y is null
    public String[] getByYear(int y){
        int number = getNumberByYear(y);
        String[] books = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getYear() == y) {
                books[pos] = current.bk.getTitle();
                pos++;
            }
            current = current.next;
        }
        return books;
    }

    // @returns: an array of string containing all the authors whose books have been published by pub contained in the library
    // @throws: NullPointerException if pub is null
    public String[] getAuthorByPublisher(String pub){
        if (pub == null)
            throw new NullPointerException();
            
        int number = getNumberBy("publisher", pub);
        String[] tempAuthors = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getPublisher().equals(pub) && 
                    !isInArray(current.bk.getAuthor(), tempAuthors, pos)){
                tempAuthors[pos] = current.bk.getAuthor();
                pos++;
            }
            current = current.next;
        }

        String[] authors = new String[pos];
        for(int i = 0; i < pos; i++) {
            authors[i] = tempAuthors[i];
        }

        return authors;
    }

    // @returns: an array of string containing all the titles of books  which have been published in a given year contained in the library
    // @throws: NullPointerException if pub is null
    public String[] getTitleByYear(int year){
        int number = getNumberByYear(year);
        String[] tempBooks = new String[number];
        int pos = 0;
        BookNode current = this.list;

        while(current != null){
            if(current.bk.getYear() == year && 
                    !isInArray(current.bk.toString(), tempBooks, pos)){
                tempBooks[pos] = current.bk.getAuthor();
                pos++;
            }
            current = current.next;
        }

        String[] books = new String[pos];
        for(int i = 0; i < pos; i++) {
            books[i] = tempBooks[i];
        }

        return books;
    }

    private int getNumberBy(String type, String cmp){
        int number = 0;
        BookNode current = this.list;

        // type must be one of "author", "title" or "publisher"
        switch (type) {
            case "author":
                while (current != null)
                    if(current.bk.getAuthor().equals(cmp)) {
                        number++;
                        current = current.next;
                    }
                break;
            case "title":
                while (current != null)
                    if(current.bk.getTitle().equals(cmp)) {
                        number++;
                        current = current.next;
                    }
                break;
            case "publisher":
                while (current != null)
                    if(current.bk.getPublisher().equals(cmp)) {
                        number++;
                        current = current.next;
                    }
                break;
            
            default:
                break;
        }
        return number;
    }

    private int getNumberByYear(int year){
        int number = 0;
        BookNode current = this.list;
        while(current != null) {
            if(current.bk.getYear() == year) {
                number++;
                current = current.next;
            }
        }
        return number;
    }

    private boolean isInArray(String s, String[] arr, int curr_length){
        if (s == null || arr == null)
            throw new NullPointerException();
    
        int length = Math.min(arr.length, curr_length);
        for(int i = 0; i < length; i++) 
            if (s.equals(arr[i]))
                return true;
        
        return false;
    }
}