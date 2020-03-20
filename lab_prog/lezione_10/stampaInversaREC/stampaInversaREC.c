#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento node;
typedef node* nodeList;

void push_front(int elem, nodeList* list);
void RecStampaInversa(nodeList list);
void clear_list(nodeList* list);

int main(){
    nodeList list = NULL;
    int elem;

    do {
        scanf("%d", &elem);
        if(elem > 0)
            push_front(elem, &list);
    } while(elem > 0);

    RecStampaInversa(list);
    printf("NULL\n");

    clear_list(&list);
    return 0;
}

void push_front(int elem, nodeList* list){
    node* new_node = malloc(sizeof(node));
    new_node->info = elem;
    new_node->next = *list;
    *list = new_node;
}

void RecStampaInversa(nodeList list){
    if(list != NULL){
        RecStampaInversa(list->next);
        printf("%d -> ", list->info);
    }
}

void clear_list(nodeList* list){
    node* to_be_deleted = NULL;
    while(*list != NULL){
        to_be_deleted = *list;
        *list = (*list)->next;
        free(to_be_deleted);
    }
}