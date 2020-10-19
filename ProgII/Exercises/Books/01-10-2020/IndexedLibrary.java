public interface IndexedLibrary extends Library {
    public IndexedBook getByIndex(int index);
    // Restituisce il volume con il codice index
    public void remove(int index) throws Exception;
    // Rimuove il libro con codice index, lancia un'eccezione
    // se il libro non e' presente
}
