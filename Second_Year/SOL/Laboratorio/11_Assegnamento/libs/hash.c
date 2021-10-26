#include "lib.h"
#include "lists.h"
#include "hash.h"
#include <stdbool.h>

static unsigned int hash_function(int n){
    return n*266489 + 7;
}

static inline void _hashtable_ins(hashtable_t* table, int elem){
    unsigned int hash = hash_function(elem) % table->nlist;
    push_back(table->list[hash], elem);
    table->nelem++;
}

static int hashtable_expand(hashtable_t* table){
    if(table == NULL){
        errno = EINVAL;
        return -1;
    }
    
    hashtable_t* new_table = NULL;

    if(hashtable_init(&new_table, table->nlist * 2) != 0){
        return -1;
    }

    for(int i = 0; i < table->nlist; i++){
        node_t* curr = table->list[i]->head;

        while(curr != NULL){
            _hashtable_ins(new_table, curr->info);
            curr = curr->next;
        }
    } 

    hashtable_free(table);
    table = new_table;
    return 0;
}

int hashtable_init(hashtable_t** table, int nlist){
    (*table) = NULL;

    if( ((*table) = malloc(sizeof(hashtable_t))) == NULL){
        errno = ENOMEM;
        return -1;
    }

    (*table)->nelem = 0;
    (*table)->nlist = nlist;

    if( ((*table)->list = malloc((*table)->nlist * sizeof(list_t*))) == NULL){
        errno = ENOMEM;
        return -1;
    }
    for(int i = 0; i < (*table)->nlist; i++){
        if( ((*table)->list[i] = malloc(sizeof(list_t))) == NULL){
            errno = ENOMEM;
            return -1;
        }
        (*table)->list[i]->nelem = 0;
        (*table)->list[i]->head = NULL;
        (*table)->list[i]->tail = NULL;
    }

    return 0;
}

int hashtable_insert(hashtable_t* table, int elem){
    if(table == NULL){
        errno = EINVAL;
        return -1;
    }

    if(table->nelem + 1 > table->nlist/2)
        hashtable_expand(table);

    unsigned int hash = hash_function(elem) % table->nlist;
    push_back(table->list[hash], elem);
    table->nelem++;

    return 0;
}

int hashtable_remove(hashtable_t* table, int elem){
    if(table == NULL){
        errno = EINVAL;
        return -1;
    }

    unsigned int hash = hash_function(elem) % table->nelem;
    node_t* curr = table->list[hash]->head;
    while(curr != NULL){
        if(curr->info == elem){
            curr->prec->next = curr->next;
            curr->next->prec = curr->prec;
            free(curr);
            table->nelem--;
            break;
        }
    }

    return 0;
}

void hashtable_free(hashtable_t* table){
    if(table == NULL) return;

    for(int i = 0; i < table->nlist; i++){
        list_delete(table->list[i]);
    }
    free(table->list);
    free(table);
}

int hashtable_iter_init(hasht_iter_t* iter){
    if(iter == NULL) {
        errno = EINVAL;
        return -1;
    }

    iter->info = -1;
    iter->current_list = -1;
    iter->current_pos = NULL;

    return 0;
}

int hashtable_iter_get_next(hashtable_t* table, hasht_iter_t* iter){
    if(table == NULL || iter == NULL){
        errno = EINVAL;
        return -1;
    }

    if(iter->current_pos != NULL){
        iter->current_pos = iter->current_pos->next;
        
        if(iter->current_pos != NULL){ // found next element in the same list
            iter->info = iter->current_pos->info;
            return 0;
        }
    }

    // list ended: must go to next list
    // searching for next non-empty list
    while(iter->current_list + 1 < table->nlist && iter->current_pos == NULL){
        iter->current_list++;
        iter->current_pos = table->list[iter->current_list]->head;
    }

    if(iter->current_pos != NULL){ // finally found it
        iter->info = iter->current_pos->info;
        return 0;
    }

    // end of hashtable
    iter->info = -2;
    iter->current_pos = NULL;
    iter->current_list = -2;

    return -2;
}