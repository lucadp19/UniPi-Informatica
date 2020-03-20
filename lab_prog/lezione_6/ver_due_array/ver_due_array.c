#include <stdio.h>

int less_than_all(int, int[], int);
int exists_less(int[], int, int[], int);

int main(){
    int a[3], b[3];
    int dim_a = 3;
    int dim_b = 3;
    int* p;

    for(p = a; p != a+dim_a; p++)
        scanf("%d", p);
    for(p = b; p != b+dim_b; p++)
        scanf("%d", p);

    if(exists_less(a, dim_a, b, dim_b))
        printf("TRUE\n");
    else
        printf("FALSE\n");
    return 0;
}

int exists_less(int a[], int dim_a, int b[], int dim_b){
    int* p = a;
    int found = 0; // found vale 1 se abbiamo trovato un elemento che soddisfa la condizione, 0 altrimenti
    while(!found && p != a+dim_a){
        if(less_than_all(*p, b, dim_b)) // se l'elemento soddisfa la condizione fermiamo il ciclo
            found = 1;
        else
            p++; // altrimenti si continua
    }
    // alla fine found vale 1 se abbiamo trovato un elemento che soddisfa la condizione
    // 0 altrimenti
    return found;
}

int less_than_all(int elem, int b[], int dim_b){
    int* p = b;
    int cont = 1; // cont vale 1 se la condizione è soddisfatta, 1 altrimenti
    while(cont && p != b+dim_b){
        if(elem < *p) // se l'elemento soddisfa la condizione si continua
            p++;
        else
            cont = 0; // altrimenti si ferma il ciclo
    }
    // alla fine cont vale 1 se la condizione è soddisfatta per tutti gli elementi
    // 0 altrimenti
    return cont;
}
