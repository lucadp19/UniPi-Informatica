#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node *next;
} node;

node* create_list(node* list, int elem){
    // la lista e' VUOTA

    list = (node*) malloc(sizeof(node));
    list->data = elem;
    list->next = NULL;

    return list;
}

node* append(node* last_elem, int elem){
    // last_elem e' l'ultimo elemento inserito in lista
    // la lista deve essere NON-VUOTA

    last_elem->next = (node*) malloc(sizeof(node));
    last_elem->next->data = elem;
    last_elem->next->next = NULL;

    return last_elem->next;
}

void push_front(node** list, int elem){
    // *list e' il primo elemento della lista
    // la lista deve essere NON-VUOTA
    
    node* new_elem = (node*) malloc(sizeof(node));
    new_elem->data = elem;
    new_elem->next = *list;

    *list = new_elem;
}

void print_list(node* list){
    while(list != NULL){
        printf("%d ", list->data);
        list = list->next;
    }
}

void free_list(node** list){
    node* aux;
    while(*list != NULL){
        aux = *list;
        *list = (*list)->next;

        free(aux);
    }
}

int main(){
    int N, elem;
    node* list = NULL;
    // solo per inserimento in coda
    // node* last_elem = NULL;
    
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &elem);
        if(list == NULL){
            list = create_list(list, elem);
            // last_elem = list;
        } else {
            // IN TESTA
            push_front(&list, elem);

            // IN CODA
            // last_elem = append(list, elem);
        }
    }

    // DO THINGS

    free_list(&list);
    return 0;
}