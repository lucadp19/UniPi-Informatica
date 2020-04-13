#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int info;
    struct _node* next;
} node;

void move_to_front(node** list, node* prec){
    node* aux = prec->next;

    prec->next = prec->next->next;
    aux->next = *list;
    *list = aux;
}

int find(node* list, node** prec, node** curr, int elem){
    int found = 0;
    int pos = 0;
    *prec = NULL;
    *curr = list;

    while(*curr != NULL && !found){
        if((*curr)->info == elem)
            found = 1;
        else{
            *prec = *curr;
            *curr = (*curr)->next;
            pos++;
        }
    }

    if(!found){
        *prec = NULL;
        *curr = NULL;
        pos = -1;
    }

    return pos;
}

int find_and_mtf(node** list, int elem){
    node* prec;
    node* curr;
    int pos = find(*list, &prec, &curr, elem);

    if(pos != 0 && pos != -1)
        move_to_front(list, prec);
        
    return pos;
}    
int main(){
    int N, elem, out;
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

    do{
        scanf("%d", &elem);
        out = find_and_mtf(&list, elem);
        printf("%d\n", out);
    } while(out != -1);
    for(int i = 0; i < N; i++){
        curr = list;
        list = list->next;
        free(curr);
    }
}