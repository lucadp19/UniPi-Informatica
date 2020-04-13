#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int info;
    int count;
    struct _node* next;
    struct _node* prec;
} node;

void update_list(node** list, node* curr){
    node* prec = curr->prec;
    prec->next = curr->next; 

    while(prec != NULL && prec->count < curr->count){
        prec = prec->prec;
    }

    if(prec == NULL){
        curr->next = *list;
        curr->prec = NULL;
        (*list)->prec = curr;
        *list = curr;
    } else{
        curr->next = prec->next;
        curr->prec = prec;
        prec->next = curr;
        if(curr->next != NULL)
            (curr->next)->prec = curr;
    }

    
}

int find(node* list, node** curr, int elem){
    int found = 0;
    int pos = 0;

    *curr = list;

    while(*curr != NULL && !found){
        if((*curr)->info == elem){
            found = 1;
            (*curr)->count++;
        }
        else{
            *curr = (*curr)->next;
            pos++;
        }
    }

    if(!found){
        *curr = NULL;
        pos = -1;
    } 

    return pos;
}

void print(node* list){
    printf("\n");
    while(list != NULL){
        if(list->prec != NULL)
            printf("%d ", list->prec->info);
        else printf("NULL ");
        printf("%d ", list->info);
        if(list->next != NULL)
            printf("%d ", list->next->info);
        else printf("NULL ");
        printf("\n");
        list = list->next;
    }
    printf("\n");
}

int find_and_update(node** list, int elem){
    node* curr;
    int pos = find(*list, &curr, elem);

    // print(*list);

    if(pos != 0 && pos != -1)
        update_list(list, curr);
        
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
        new_node->prec = curr;
        new_node->count = 0;

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
        out = find_and_update(&list, elem);
        printf("%d\n", out);
    } while(out != -1);
    
    for(int i = 0; i < N; i++){
        curr = list;
        list = list->next;
        free(curr);
    }
}