#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct _item {
    string name;
    string telephone;
    struct _item* next;
} item;


int n;

int h(string s){
    unsigned int sum = 0;
    while(*s != '\0'){
        sum += (unsigned int)(*s) % (2*n);
        sum = sum % (2*n);
        s++;    
    }
    sum = sum % (2*n);
    return sum;
}

void insert_ord_in_list(item** list, string name, string telephone){
    item* new_elem;

    if(*list == NULL || strcmp((*list)->name, name) >= 0){
        new_elem = (item*) malloc(sizeof(item));
        new_elem->name = name;
        new_elem->telephone = telephone;
        new_elem->next = *list;

        (*list) = new_elem;
    }
    else {
        insert_ord_in_list(&((*list)->next), name, telephone);
    }
}

int length(item* list){
    int len = 0;
    while(list != NULL){
        len++;
        list = list->next;
    }

    return len;
}

void print_list(item* list){
    while(list != NULL){
        printf("%s %s\n", list->name, list->telephone);
        list = list->next;
    }
}

void clear_list(item** list){
    item* aux;
    while(*list != NULL){
        aux = *list;
        (*list) = (*list)->next;
        free(aux->name);
        free(aux->telephone);
        free(aux);
    }
}

int main(){
    item **T;
    int hash, K;
    string name, telephone;

    scanf("%d", &n);

    T = (item **) malloc(2*n*sizeof(item*));
    for(int i = 0; i < 2*n; i++)
        T[i] = NULL;
    
    for(int i = 0; i < n; i++){
        name = (string) malloc(101*sizeof(char));
        telephone = (string) malloc(21*sizeof(char));
        scanf("%s", name);
        scanf("%s", telephone);
        hash = h(name);
        insert_ord_in_list(&T[hash], name, telephone);
    }

    scanf("%d", &K);

    print_list(T[K]);

    for(int i = 0; i < 2*n; i++)
        clear_list(&T[i]);
    free(T);

    return 0;
}