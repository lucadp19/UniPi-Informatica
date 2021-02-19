public interface Book {
    public String getAuthor( );
    // Restituisce la stringa che corrisponde al nome dell'autore del libro
    public String getTitle( );
    // Restituisce la stringa che corrisponde al titolo del libro
    public String getPublisher( );
    // Restituisce la stringa che corrisponde all'editore del libro
    public int getYear( );
    // Restituisce l'intero che corrisponde all'anno di pubblicazione del libro
    public boolean sameAuthor(Book b);
    // Restituisce true se l'oggetto b ha lo stesso autore di this
    public boolean sameTitle(Book b);
    // Restituisce true se l'oggetto b ha lo stesso titolo di this
    public boolean samePublisher(Book b);
    // Restituisce true se l'oggetto b ha lo stesso editore di this
    public boolean sameYear(Book b);
    // Restituisce true se l'oggetto b ha lo stesso anno di pubblicazione di this
    public boolean sameWork(Book b);
    // Restituisce true se l'oggetto b e' la stessa opera di this
    public boolean equals(Book b);
    // Restituisce true se l'oggetto b e' lo stesso libro di this
}

