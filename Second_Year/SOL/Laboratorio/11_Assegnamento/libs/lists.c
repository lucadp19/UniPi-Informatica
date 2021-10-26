#include "lists.h"
#include "lib.h"


void push_back(list_t* list, int new_elem){
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

int pop_back(list_t* list){
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

void push_front(list_t* list, int new_elem){
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->info = new_elem;
    new_node->next = NULL;

    if(list->nelem == 0){
        new_node->prec = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prec = new_node;
        list->head = new_node;
    }
    list->nelem++;
}

int pop_front(list_t* list){
    if(list->nelem == 0)
        return -2;

    node_t* ptx = NULL;
    int info;
    ptx = list->head;
    if(list->nelem == 1){
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prec = NULL;
    }
    list->nelem--;
    info = ptx->info;
    free(ptx);
    return info;
}

void list_delete(list_t* list){
    if(list == NULL) return;
    
    while(list->head != NULL){
        node_t* tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    free(list);
}