#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>


struct _node_t {
    int info;
    struct _node_t* next;
    struct _node_t* prec;
};
typedef struct _node_t node_t;

struct _list_t {
    node_t* head;
    node_t* tail;
    size_t nelem;
};

typedef struct _list_t list_t;

#define INITIALIZE_LIST(list) \
    (list)->nelem = 0; \
    (list)->head = NULL; \
    (list)->tail = NULL;


void push_back(list_t* list, int new_elem);
int pop_back(list_t* list);

void push_front(list_t* list, int new_elem);
int pop_front(list_t* list);

void list_delete(list_t* list);

#endif