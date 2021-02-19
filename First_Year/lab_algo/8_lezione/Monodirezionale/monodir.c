#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int info;
    struct _node* next;
} node;

void rec_inverse_print(node* list){
    if(list != NULL){
        rec_inverse_print(list->next);

        printf("%d\n", list->info);
    }
}

int main(){
    int N, elem;
    node* list = NULL;
    node* curr = NULL;
    node* new_node = NULL;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &elem);

        new_node = (node*) malloc(sizeof(node));
        new_node->info = elem;
        new_node->next = NULL;

        if(list == NULL){
            list = new_node;
            curr = new_node;
        } else {
            curr->next = new_node;
            curr = curr->next;
        }
    }

    rec_inverse_print(list);

    for(int i = 0; i < N; i++){
        curr = list;
        list = list->next;
        free(curr);
    }
}