#include <stdio.h>
#include <stdlib.h>

struct elemento{
    int info;
    struct elemento* next;
};
typedef struct elemento node;
typedef node* list;

void pushElementToList(int, list*);
void cancRec(int, list*);
void cancList(list*);

int main(){

}

void pushElementToList(int elem, list* lista){
    node* new_elem = malloc(sizeof(node));
    new_elem->info = elem;
    new_elem->next = *lista;
    *lista = new_elem;
}

void cancRec(int n, list* lista){
    
}