#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento ElementoDiLista;
typedef ElementoDiLista* ListaDiElementi;

void printList(ListaDiElementi);
void pushBack(ListaDiElementi*, int);
void pushFront(ListaDiElementi*, int);
void removeElement(ListaDiElementi*, int);
void clearList(ListaDiElementi*);

int main(){
    ListaDiElementi list = NULL;
    int choice;

    do {
        scanf("%d", &choice);
        if(choice > 0){
            if(choice%2 == 0)
                pushFront(&list, choice);
            else
                pushBack(&list, choice);
        }
        else if (choice < 0)
            removeElement(&list, choice);
        else
            printList(list);
    } while(choice != 0);

    // pulizia della lista per evitare memory leak
    clearList(&list);
    printList(list);
    
    return 0;
}

void printList(ListaDiElementi list){
    while(list != NULL){
        printf("%d\n", list->info);
        list = list->next;
    }
}

void pushBack(ListaDiElementi* list, int elem){
    ElementoDiLista* curr = *list;

    if(*list == NULL){
        *list = malloc(sizeof(ElementoDiLista));
        (*list)->info = elem;
        (*list)->next = NULL;
    }
    else {
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = malloc(sizeof(ElementoDiLista));
        curr = curr->next;
        curr->info = elem;
        curr->next = NULL;
    }
}

void pushFront(ListaDiElementi* list, int elem){
    ElementoDiLista* new_elem = malloc(sizeof(ElementoDiLista));
    new_elem->info = elem;
    new_elem->next = *list;
    *list = new_elem;
}

void removeElement(ListaDiElementi* list, int elem){
    ElementoDiLista* curr = *list;
    ElementoDiLista* prec = NULL;

    if(elem < 0)
        elem *= -1;

    if(curr == NULL)
        return;

    if(curr->info == elem){
        *list = (*list)->next;
        free(curr);
    }
    else{
        while(curr != NULL && curr->info != elem){
            prec = curr;
            curr = curr->next;
        }
        if(curr != NULL){
            prec->next = curr->next;
            free(curr);
        }
    }    
}

void clearList(ListaDiElementi* list){
    ElementoDiLista* curr = *list;
    while(*list != NULL){
        *list = (*list)->next;
        free(curr);
        curr = *list;
    }
}