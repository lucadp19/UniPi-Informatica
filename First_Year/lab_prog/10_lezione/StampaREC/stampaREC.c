#include <stdio.h>
#include <stdlib.h>

struct elemento{
	int info;
	struct elemento* next;
};
typedef struct elemento node;
typedef node* list;

void RecStampa(list);
void pushElementToList(int, list*);
void clearList(list*);

int main(){
	int num;
	list lista = NULL;
	do {
		scanf("%d", &num);
        if(num >= 0)
		    pushElementToList(num, &lista);
	} while (num >= 0);
	RecStampa(lista);

	clearList(&lista);

	return 0;
}

void pushElementToList(int elem, list* lista){
	node* new_elem = malloc(sizeof(node));
	new_elem->info = elem;
	new_elem->next = *lista;
	*lista = new_elem;	
}

void clearList(list* lista){
	node* elem;
	while(*lista != NULL){
		elem = *lista;
		*lista = (*lista)->next;
		free(elem);
	}
}

void RecStampa(list lista){
	if(lista != NULL){
		printf("%d -> ", lista->info);
		RecStampa(lista->next);
	}
	else printf("NULL\n");
}
