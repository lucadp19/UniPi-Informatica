#ifndef _HASH_H
#define _HASH_H

#include "lib.h"
#include "lists.h"

#define DEFAULT_NLIST 128

typedef struct {
    int nelem;
    int nlist;
    list_t** list;
} hashtable_t;

typedef struct {
    int info;
    int current_list;
    node_t* current_pos;
} hasht_iter_t;

int hashtable_init(hashtable_t** table, int nlist);
int hashtable_insert(hashtable_t* table, int elem);
int hashtable_remove(hashtable_t* table, int elem);
void hashtable_free(hashtable_t* table);

int hashtable_iter_init(hasht_iter_t* iter);
int hashtable_iter_get_next(hashtable_t* table, hasht_iter_t* iter);
// int hashtable_iter_prev(hashtable_t* table, hasht_iter_t* iter);
// int hashtable_iter_close(hashtable_t* table, hasht_iter_t* iter);

#endif