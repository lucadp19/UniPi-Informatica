#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct _node {
    int value;
    string name;
    struct _node* next;
} item;

typedef struct{
    int value;
    string name;
} pair;

int N;

int min(int a, int b){
    if (a < b) return a;
    else return b;
}

int h(string s){
    unsigned int sum = 0;
    while(*s != '\0'){
        sum += (unsigned int)(*s) % (2*N);
        sum = sum % (2*N);
        s++;    
    }
    sum = sum % (2*N);
    return sum;
}

void insert_in_list(item** list, string name, int value){
    item* new_elem = (item*) malloc(sizeof(item));
    new_elem->name = name;
    new_elem->value = value;
    new_elem->next = *list;
    
    *list = new_elem;
}

int find_and_update(item* list, string name, int value){
    while(list != NULL){
        if(strcmp(list->name, name) == 0){
            if(value > list->value)
                list->value = value;
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void print_list(item* list){
    while(list != NULL){
        printf("(%s, %d), ", list->name, list->value);
        list = list->next;
    }
}

void print_hash_table(item** table){
    for(int i = 0; i < 2*N; i++){
        printf("%d: ", i);
        print_list(table[i]);
        printf("\n");
    }
}

void clear_list(item** list){
    item* aux;
    while(*list != NULL){
        aux = *list;
        (*list) = (*list)->next;
        free(aux->name);
        free(aux);
    }
}

int cmp(const void* a, const void* b){
    item** p1 = (item**) a;
    item** p2 = (item**) b;

    if((*p1)->value == (*p2)->value)
        return strcmp((*p1)->name, (*p2)->name);
    else return (*p2)->value - (*p1)->value;
}

int main(){
    item **T;
    int v;
    int inserted = 0;
    int aux_ins;
    item** best_items;
    unsigned int hash;
    string s;

    scanf("%d", &N);

    T = (item **) malloc(2*N*sizeof(item*));
    for(int i = 0; i < 2*N; i++)
        T[i] = NULL;
    
    for(int i = 0; i < N; i++){
        s = (string) malloc(101*sizeof(char));
        scanf("%s", s);
        scanf("%d", &v);
        hash = h(s);
        if(!find_and_update(T[hash], s, v)) {
            insert_in_list(&T[hash], s, v);
            inserted++;
        }
        else free(s);
    }

    // print_hash_table(T);

    aux_ins = 0;
    best_items = (item**) malloc(inserted*sizeof(item*));
    for(int i = 0; i < 2*N; i++){
        // printf("List %d, left to insert %d\n", i, aux_ins);
        item* list = T[i];
        while(list != NULL){
            // printf("GOT INTO THE LIST NUMBER %d!\n", i);
            best_items[aux_ins++] = list;
            list = list->next;
        }
    }

    // for(int i = 0; i < inserted; i++)
    //     printf("(%s, %d); ", best_items[i]->name, best_items[i]->value);
    // printf("\n");

    qsort(best_items, inserted, sizeof(item*), cmp);

    // for(int i = 0; i < inserted; i++)
    //     printf("(%s, %d); ", best_items[i]->name, best_items[i]->value);
    // printf("\n");

    inserted = min(inserted, 15);

    for(int i = 0; i < inserted; i++)
        printf("%s\n", best_items[i]->name);

    for(int i = 0; i < 2*N; i++)
        clear_list(&T[i]);
    free(T);
    free(best_items);

    return 0;
}