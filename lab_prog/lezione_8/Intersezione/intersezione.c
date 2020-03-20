#include <stdlib.h>
#include <stdio.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento ElementoDiLista;
typedef ElementoDiLista* ListaDiElementi;

void printList(ListaDiElementi);
void orderedInsert(ListaDiElementi*, int);
ListaDiElementi intersectOrderedLists(ListaDiElementi, ListaDiElementi);
int existsElement (int, ListaDiElementi);
void clearList(ListaDiElementi*);

int main(){
    ListaDiElementi l1 = NULL;
    ListaDiElementi l2 = NULL;
    ListaDiElementi l3 = NULL;
    int elem;

    do {
        scanf("%d", &elem);
        if(elem > 0)
            orderedInsert(&l1, elem);   
    } while (elem > 0);

    do {
        scanf("%d", &elem);
        if(elem > 0)
            orderedInsert(&l2, elem);   
    } while (elem > 0);

    l3 = intersectOrderedLists(l1, l2);

    printList(l3);

    clearList(&l1);
    clearList(&l2);
    clearList(&l3);

    return 0;
}

void printList(ListaDiElementi list){
    while(list != NULL){
        printf("%d\n", list->info);
        list = list->next;
    }
    printf("\n");
}

void orderedInsert(ListaDiElementi* list, int elem){
    ElementoDiLista* curr = *list;
    ElementoDiLista* prec = NULL;
    ElementoDiLista* new_elem;

    if (*list == NULL){
        new_elem = malloc(sizeof(ElementoDiLista));
        new_elem->info = elem;
        new_elem->next = NULL;
        *list = new_elem;
    }
    else if ((*list)->info > elem){
        new_elem = malloc(sizeof(ElementoDiLista));
        new_elem->info = elem;
        new_elem->next = *list;
        *list = new_elem;
    }
    else {
        while (curr != NULL && curr->info < elem){
            prec = curr;
            curr = curr->next;
        }
        if (curr == NULL || curr->info != elem){
            new_elem = malloc(sizeof(ElementoDiLista));
            new_elem->info = elem;
            new_elem->next = curr;
            prec->next = new_elem;
        }
    }
}

ListaDiElementi intersectOrderedLists(ListaDiElementi a, ListaDiElementi b){
    ListaDiElementi result = NULL;
    ElementoDiLista* curr = a;

    while(curr != NULL){
        if(existsElement(curr->info, b))
            orderedInsert(&result, curr->info);
        curr = curr->next;
    }

    return result;
}

int existsElement(int elem, ListaDiElementi list){
    ElementoDiLista* curr = list;
    int found = 0;

    while(!found && curr != NULL && curr->info <= elem){
        if(curr->info == elem) found = 1;
        else curr = curr->next;
    }
    
    return found;
}

void clearList (ListaDiElementi* list){
    ElementoDiLista* curr = *list;
    while(*list != NULL){
        *list = (*list)->next;
        free(curr);
        curr = *list;
    }
}