public interface IndexedBook extends Book {
    public int getIndex();
    // Restituisce l'intero che corrisponde al codice identificativo del libro
    public String getGenre();
    // Restituisce la stringa che corrisponde al genere del libro
    public boolean sameGenre(IndexedBook b);
    // Restituisce true se l'oggetto b appartiene allo stesso genere di this
}

