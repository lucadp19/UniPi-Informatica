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

int sum_list(node* list){
    int sum = 0;
    while(list != NULL){
        sum += list->data;
        list = list->next;
    }
    return sum;
}

void delete_elements(node** list, int media){
    node* aux;
    if((*list) != NULL){
        if((*list)->data <= media){
            aux = (*list);
            (*list) = (*list)->next;
            free(aux);

            delete_elements(list, media);
        }
        else
            delete_elements(&((*list)->next), media);
    }
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
    int N, elem, media;
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

    media = (int)((float)sum_list(list)/N);

    printf("%d\n", media);

    print_list(list);

    delete_elements(&list, media);
    print_list(list);

    clear_list(&list);
    return 0;
}