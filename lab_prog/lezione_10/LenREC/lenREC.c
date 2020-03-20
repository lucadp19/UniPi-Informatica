#include <stdio.h>
#include <stdlib.h>

struct elemento{
    int info;
    struct elemento* next;
};
typedef struct elemento node;
typedef node* list;

void pushElementToList(int, list*);
int RecLength(list);
void clearList(list*);

int main(){
    list lista = NULL;
    int elem;

    do {
        scanf("%d", elem);
        if(elem >= 0)
            pushElementToList(elem, &lista);
    } while (elem >= 0);

    printf("%d", RecLength(lista));
    clearList(&lista);

    return 0;
}

void pushElementToList(int elem, list* lista){
    node* new_elem = malloc(sizeof(node));
    new_elem->info = elem;
    new_elem->next = *lista;
    *lista = new_elem;
}

int RecLength(list lista){
    if(lista == NULL)
        return 0;
    else
        return 1 + RecLength(lista->next);
}

void clearList(list* lista){
    node* first;
    while(*lista != NULL){
        first = *lista;
        *lista = (*lista)->next;
        free(next);
    }
}