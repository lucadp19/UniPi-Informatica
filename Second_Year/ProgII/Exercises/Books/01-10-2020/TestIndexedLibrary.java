public class TestIndexedLibrary {
    // TestIL
    public static void main (String[ ] args) {
        Book myBk1 = new MyBook("autore1", "titolo1", "editore1", 1900);
        Book myBk2 = new MyBook("autore2", "titolo2", "editore1", 2000);
 
        Library myL = new MyLibrary( );
        myL.insert(myBk1);
        myL.insert(myBk2);

        IndexedBook myBk3 = new MyIndexedBook("autore3", "titolo3", "editore3", 1966, 0, "fiction");
        myL.insert(myBk3);
        
        assert myBk3.getGenre().equals("fiction");
        /*
         per verificare la versione estesa di book
         */
        
        IndexedLibrary myIL = new MyIndexedLibrary( );
        myIL.insert(myBk1);
        myIL.insert(myBk2);
        myIL.insert(myBk3);

        /*
         System.out.println(myBk2);
         System.out.println(myIL.getByIndex(2));
         */
        assert myIL.getByIndex(2).equals(myBk2);
        
        /*
         per verificare la versione estesa di library;
         la correttezza dell'assert dipende dalla specifica
         implementazione dell'indicizzazione
         */
    }
}
