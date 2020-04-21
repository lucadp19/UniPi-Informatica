#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node* next;
} node;

node* create_list(node* list, int elem){
    list = (node*) malloc(sizeof(node));
    list->data = elem;
    list->next = NULL;
    
    return list;
}

node* back_insert(node* last_elem, int elem){
    last_elem->next = (node*) malloc(sizeof(node));
    last_elem->next->data = elem;
    last_elem->next->next = NULL;

    return last_elem->next;
}

int suffix_sum_list(node* list){
    int current_value;

    if(list == NULL)
        return 0;
    
    current_value = list->data;
    list->data = suffix_sum_list(list->next);

    return current_value+list->data;
}

void print_list(node* list){
    while (list != NULL){
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

void clear_list(node** list){
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
    node* last_elem = NULL;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &elem);

        if(list == NULL){
            list = create_list(list, elem);
            last_elem = list;
        } else
            last_elem = back_insert(last_elem, elem);
    }

    print_list(list);

    suffix_sum_list(list);
    print_list(list);

    clear_list(&list);
    return 0;
}