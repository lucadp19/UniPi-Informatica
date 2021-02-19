/**
 * A MyIndexedLibrary is a collection of indexed book, which means books with a unique index.
 */
public class MyIndexedLibrary extends MyLibrary implements IndexedLibrary {
    private class IndexedBookNode extends BookNode {
        private int index;

        public IndexedBookNode(Book bk, int index){
            super(bk, null);
            this.index = index;
        }
    
        public IndexedBookNode(Book bk, BookNode next, int index){
            super(bk, next);
            this.index = index;
        }
    }

    private int nextIndex;

    public MyIndexedLibrary(){
        list = null;
        nextIndex = 0;
    }

    public MyIndexedLibrary(Book bk, int firstIndex){
        if (bk == null)
            throw new NullPointerException();

        list = new IndexedBookNode(bk, firstIndex);
        nextIndex = firstIndex + 1;
    }

    public MyIndexedLibrary(Book bk){
        this(bk, 0);
    }

    public void insert(Book bk){
        if (bk == null)
            throw new NullPointerException();
        
        IndexedBookNode newNode = new IndexedBookNode(bk, this.list, nextIndex);
        list = newNode;
        nextIndex += 1;
    }

    public IndexedBook getByIndex(int index){
        IndexedBookNode current = (IndexedBookNode)list;
        while(current != null){
            if (current.index == index)
                return (IndexedBook)current.bk;
        }
        return null;
    }

    public void remove(int index) throws IndexNotFoundException{
        IndexedBookNode current = (IndexedBookNode)this.list;
        IndexedBookNode previous = null;
        boolean foundIndex = false;

        if(current.index == index){
            foundIndex = true;
            this.list = this.list.next;
        }
        while (!foundIndex && current != null){
            if(current.index == index){
                foundIndex = true;
                previous.next = current.next;
                current = (IndexedBookNode)current.next;
            }
            else {
                previous = current;
                current = (IndexedBookNode)current.next;
            }
        }

        if(!foundIndex)
            throw new IndexNotFoundException("MyIndexedLibrary.remove: index not found in list");
    }
    
}