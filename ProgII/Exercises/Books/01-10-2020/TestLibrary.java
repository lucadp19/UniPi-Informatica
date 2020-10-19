public class TestLibrary {
    // TestL
    public static void main (String[ ] args) {
        Book myBk1 = new MyBook("autore1", "titolo1", "editore1", 1900);
        Book myBk2 = new MyBook("autore2", "titolo2", "editore1", 2000);
 
        Library myL = new MyLibrary( );
        myL.insert(myBk1);
        myL.insert(myBk2);
 
        assert ((myL.getAuthorByPublisher("editore1"))[0]).equals("autore2");
        /*
         la correttezza dell'assert dipende dalla specifica
         implementazione dell'estrazione
         */

        try {
            myL.remove(myBk2);
            myL.remove(myBk2);
        }
        catch (Exception exc) {
            System.out.println("Ben fatto!");
            System.out.println(exc);
        }
    }
}
