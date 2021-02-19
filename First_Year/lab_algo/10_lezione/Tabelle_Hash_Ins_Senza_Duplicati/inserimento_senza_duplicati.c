#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* prec;
    struct _node* next;
} item;

int a;
int b;
int p;
int n;

int h(int x){
    return ((a*x + b) % p) % (2*n);
}

void insert_in_list(item** list, int elem){
    item* new_elem = (item*) malloc(sizeof(item));
    new_elem->data = elem;
    new_elem->prec = NULL;
    new_elem->next = *list;
    if(*list != NULL)
        (*list)->prec = new_elem;
    
    *list = new_elem;
}

int find(item* list, int elem){
    while(list != NULL){
        if(list->data == elem)
            return 1;
        list = list->next;
    }
    return 0;
}

int length(item* list){
    int len = 0;
    while(list != NULL){
        // printf("%d -> ", list->data);

        len++;
        list = list->next;
    }
    // printf("NULL\n");
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
    int max_len = 0;
    int conflicts = 0;
    int inserted = 0;
    int curr_len;

    scanf("%d %d %d", &n, &a, &b);
    p = 999149;

    T = (item **) malloc(2*n*sizeof(item*));
    for(int i = 0; i < 2*n; i++)
        T[i] = NULL;
    
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        hash = h(x);
        if(!find(T[hash], x)){
            insert_in_list(&T[hash], x);
            inserted++;
        }
    }

    for(int i = 0; i < 2*n; i++){
        curr_len = length(T[i]);

        if(curr_len > 0){
            conflicts += curr_len - 1;
            if(max_len < curr_len)
                max_len = curr_len;
        }
    }

    printf("%d\n%d\n%d\n", conflicts, max_len, inserted);

    for(int i = 0; i < 2*n; i++)
        clear_list(&T[i]);
    free(T);

    return 0;
}