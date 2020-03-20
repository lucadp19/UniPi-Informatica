#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento ElementoDiLista;
typedef ElementoDiLista* ListaDiElementi;

void printList(ListaDiElementi);
ListaDiElementi addElement(ListaDiElementi, int);
ListaDiElementi removeElement(ListaDiElementi);

int main(){
    int choice;
    ListaDiElementi list = NULL;

    do {
        scanf("%d", &choice);
        if(choice > 0)
            list = addElement(list, choice);
        else if (choice == 0)
            list = removeElement(list);
        else
            printList(list);
    } while(choice >= 0);

    // pulizia della lista per evitare memory leak
    while(list != NULL)
        list = removeElement(list);
    
    return 0;
}

void printList(ListaDiElementi list){
    while(list != NULL){
        printf("%d\n", list->info);
        list = list->next;
    }
}

ListaDiElementi addElement(ListaDiElementi list, int elem){
    ElementoDiLista* new_elem = malloc(sizeof(ElementoDiLista));
    new_elem->info = elem;
    new_elem->next = list;
    list = new_elem;
    return list;
}

ListaDiElementi removeElement(ListaDiElementi list){
    if(list != NULL){
        ElementoDiLista* head = list;
        list = list->next;
        free(head);
    }
    return list;
}