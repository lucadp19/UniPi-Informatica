#include <stdio.h>
#include <stdlib.h>

// List structure:
struct El {
    int info;
    struct El *next;
};
typedef struct El ElementoLista;

// Functions/Procedure to be implemented:

ElementoLista* readList(ElementoLista **list, int dis);
int maxDistance(ElementoLista *list);
ElementoLista* CancellaMax(ElementoLista **list, int maxdis);
int abs(int n);

// Function to print all the elements of the list:
void printList(ElementoLista *list){
    printf("(");
    while (list != NULL){
        printf("%d ", list->info);
        list = list->next;
    }
    printf(")\n");
}

int main() {
    ElementoLista *list = NULL;
    ElementoLista *list_aux = NULL;
    int boundis, maxdis;

    //Read the bounded distance
    scanf("%d", &boundis);

    //Read and print the list
    list_aux = readList(&list, boundis);
    printf("La lista bounded-%d e':\n", boundis);
    if (list_aux != NULL) {
        list = list_aux;
        list_aux = NULL;
    }
    printList(list);

    // Compute and print the maxdistance of the list
    maxdis = maxDistance(list);
    printf("La distanza massima e':\n%d\n", maxdis);

    // Removes the elements oat a distance maxdistance
    list_aux = CancellaMax(&list, maxdis);
    printf("La lista modificata e':\n");
    if (list_aux != NULL) list = list_aux;
    printList(list);

    return 0;
}

int abs(int n){
    // Takes a number n and returns its absolute value
    if(n >= 0) return n;
    else return -n;
}

ElementoLista* readList(ElementoLista **list, int dis) {
    ElementoLista* new_elem = malloc(sizeof(ElementoLista));
    ElementoLista* curr_elem;
    int prec, curr, last_dist;

    // the first element is always in the list
    scanf("%d", &curr);
    new_elem->info = curr;
    new_elem->next = NULL;
    *list = new_elem;
    curr_elem = *list;

    do {
        // the old current element becomes prec
        prec = curr;

        scanf("%d", &curr);
        last_dist = abs(curr-prec);

        // if the distance is less or equal to the bound
        if(last_dist <= dis) {
            // append the new node to the list
            new_elem = malloc(sizeof(ElementoLista));
            new_elem->info = curr;
            new_elem->next = NULL;

            // and slide foward the curr_elem pointer
            curr_elem->next = new_elem;
            curr_elem = curr_elem->next; 
        }
    } while(last_dist <= dis);

    return *list;
}

int maxDistance(ElementoLista* list) {
    int curr_dist;    
    int curr_max = abs(list->next->info - list->info);

    list = list->next;
    while (list->next != NULL) {
        curr_dist = abs(list->next->info - list->info);
        if(curr_dist > curr_max)
            curr_max = curr_dist;
        list = list->next;
    }
    
    return curr_max;
}

ElementoLista* CancellaMax(ElementoLista **list, int maxdis) {
    ElementoLista* to_be_deleted;
    
    if((*list)->next != NULL) {
        if(abs((*list)->next->info - (*list)->info) == maxdis){
            to_be_deleted = *list;
            *list = (*list)->next;
            free(to_be_deleted);
            *list = CancellaMax(list, maxdis);
        }
        else
            (*list)->next = CancellaMax(&((*list)->next), maxdis);
    }
    
    return *list;
}