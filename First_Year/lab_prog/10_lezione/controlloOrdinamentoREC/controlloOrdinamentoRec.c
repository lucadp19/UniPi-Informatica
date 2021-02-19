#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *next;
};
typedef struct elemento node;
typedef node* nodeList;

typedef enum{false, true} boolean;

void push_back(int elem, nodeList* list);
boolean isStrictlyIncreasing(nodeList list);
void clear_list(nodeList* list);

int main(){
    nodeList list = NULL;
    int elem;

    do {
        scanf("%d", &elem);
        if(elem > 0)
            push_back(elem, &list);
    } while(elem > 0);

    if(isStrictlyIncreasing(list))
        printf("True\n");
    else 
        printf("False\n");

    clear_list(&list);
    return 0;
}

void push_back(int elem, nodeList* list){
    if(*list == NULL){
        node* new_node = malloc(sizeof(node));
        new_node->info = elem;
        new_node->next = *list;
        *list = new_node;
    } else push_back(elem, &((*list)->next));
}

boolean isStrictlyIncreasing(nodeList list){
    boolean result;
    if(list->next == NULL)
        result = true;
    else {
        if(list->info >= list->next->info)
            result = false;
        else
            result = isStrictlyIncreasing(list->next);
    }

    return result;
}

void clear_list(nodeList* list){
    node* to_be_deleted = NULL;
    while(*list != NULL){
        to_be_deleted = *list;
        *list = (*list)->next;
        free(to_be_deleted);
    }
}