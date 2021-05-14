#include "lists.h"
#include "lib.h"


void push(list_t* list, int new_elem){
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->info = new_elem;
    new_node->next = NULL;

    if(list->nelem == 0){
        new_node->prec = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->prec = list->tail;
        list->tail = new_node;
    }
    list->nelem++;
}

int pop(list_t* list){
    if(list->nelem == 0)
        return -2;

    node_t* ptx = NULL;
    int info;
    ptx = list->tail;
    if(list->nelem == 1){
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prec;
        list->tail->next = NULL;
    }
    list->nelem--;
    info = ptx->info;
    free(ptx);
    return info;
}