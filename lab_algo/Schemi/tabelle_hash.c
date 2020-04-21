#include <stdio.h>
#include <stdlib.h>

typedef struct _item {
    int data;
    struct _item* prec;
    struct _item* next;
} item;


int n;

int h(int x){
    // INSERT HASH FUNCTION
}


item* create_list(node* list, int elem){
    // la lista e' VUOTA
    
    list = (node*) malloc(sizeof(node));
    list->data = elem;
    list->next = NULL;
    list->prec = NULL

    return list;
}

void insert_in_list(item** list, int elem){
    // *list e' il primo elemento della lista
    // la lista deve essere NON-VUOTA

    item* new_elem = (item*) malloc(sizeof(item));
    new_elem->data = elem;
    new_elem->prec = NULL;
    new_elem->next = *list;
    (*list)->prec = new_elem;
    
    *list = new_elem;
}

int length(item* list){
    int len = 0;
    while(list != NULL){
        len++;
        list = list->next;
    }

    return len;
}

void clear_list(item** list){
    item* aux;
    while(*list != NULL){
        aux = *list;
        (*list) = (*list)->next;
        free(aux);
    }
}

int main(){
    item **T;
    int x, hash;

    scanf("%d", &n);
    // scanf("%d %d", &a, &b);
    // p = 999149;

    T = (item **) malloc(2*n*sizeof(item*));
    for(int i = 0; i < 2*n; i++)
        T[i] = NULL;
    
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        hash = h(x);
        if(T[hash] == NULL)
            T[hash] = create_list(T[hash], x);
        else 
            insert_in_list(&T[hash], x);
    }

    // DO THINGS

    for(int i = 0; i < 2*n; i++)
        clear_list(&T[i]);
    free(T);

    return 0;
}