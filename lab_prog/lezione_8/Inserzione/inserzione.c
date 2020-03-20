#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento ElementoDiLista;
typedef ElementoDiLista* ListaDiElementi;

void orderedInsert(ListaDiElementi*, int);
void printList(ListaDiElementi);
void clearList(ListaDiElementi*);

int main(){
    ListaDiElementi list = NULL;
    int elem;

    do {
        scanf("%d", &elem);
        if(elem >= 0)
            orderedInsert(&list, elem);
        else
            printList(list);
    } while(elem >= 0);

    clearList(&list);
    return 0;
}

void printList(ListaDiElementi list){
    while(list != NULL){
        printf("%d\n", list->info);
        list = list->next;
    }
}

void orderedInsert(ListaDiElementi* list, int elem){
    ElementoDiLista* curr = *list;
    ElementoDiLista* prec = NULL;
    ElementoDiLista* new_elem;

    if(*list == NULL){
        new_elem = malloc(sizeof(ElementoDiLista));
        new_elem->info = elem;
        new_elem->next = NULL;
        *list = new_elem;
    }
    else if((*list)->info >= elem){
        new_elem = malloc(sizeof(ElementoDiLista));
        new_elem->info = elem;
        new_elem->next = *list;
        *list = new_elem;
    }
    else {
        while(curr != NULL && curr->info < elem){
            prec = curr;
            curr = curr->next;
        }
        new_elem = malloc(sizeof(ElementoDiLista));
        new_elem->info = elem;
        new_elem->next = curr;
        prec->next = new_elem;
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