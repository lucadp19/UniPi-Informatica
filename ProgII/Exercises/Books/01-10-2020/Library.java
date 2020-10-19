public interface Library {
    public String[] getByAuthor(String aut);
    // Restituisce l'elenco dei titoli con lo stesso autore aut
    public String[] getByTitle(String tit);
    // Restituisce l'elenco dei libri che hanno titolo tit
    public String[] getByPublisher(String pub);
    // Restituisce l'elenco dei libri pubblicati da pub
    public String[] getByYear(int y);
    // Restituisce l'elenco dei libri pubblicati nell'anno y

    public String[] getAuthorByPublisher(String pub);
    // Restituisce l'elenco degli autori che hanno pubblicato per pub
    
    public String[] getTitleByYear(int year);
    // Restituisce l'elenco dei titoli di libri pubblicati nell'anno year

    public void remove(Book b) throws Exception;
    // Rimuove tutti i libri identici a b dalla libreria, lancia un'eccezione
    // se il libro non e' presente
    
    public void insert(Book b);
    // Inserisce il libro b nella libreria
}

