#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char* string;

void swap(string* a, string* b){
    string tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 
  !!!!!!!!!!!! D A  F A R E !!!!!!!!!!!!
  sx e dx sono le posizioni del primo e dell'ultimo elemento dell'array mentre 
  px è la posizione dell'elemento perno.
  La funzione deve restituire la posizione del perno dopo che gli elementi sono 
  stati partizionati.
*/
int distribuzione(string a[], int sx, int px, int dx) { 
    string pivot;
    int i = sx - 1;
    int j = sx;

    swap(&a[px], &a[dx]);
    px = dx;
    pivot = a[px];

    for(j = sx; j < dx; j++)
        if(strcmp(a[j], pivot) <= 0) {
            i++;
            swap(&a[i], &a[j]);
        }
    
    swap(&a[dx], &a[i+1]);
    return i + 1;
}

void quicksort( string a[], int sx, int dx ) {
  
    int perno, pivot;
    if( sx < dx ) {
        /* DA IMPLEMENTARE: scelta del pivot. Scegliere una posizione a caso tra sx e dx inclusi. */
        pivot = rand()%(dx - sx + 1) + sx;

        perno = distribuzione(a, sx, pivot, dx); /* separa gli elementi minori di a[pivot] 
                                da quelli maggiori o uguali */
        /* Ordina ricorsivamente le due metà */
        quicksort(a, sx, perno-1);
        quicksort(a, perno+1, dx);
        
    }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(string **a, int *len) {

    int i;
    scanf("%d", len);
    if(*len <= 0) return 1;

    *a = (string *) malloc(*len * sizeof(string));
    if(*a == NULL) return 1;

    for( i = 0; i < *len; i++ ){
        (*a)[i] = (string) malloc(101 * sizeof(char));
        scanf("%s", (*a)[i]);
    }
  
    return 0;

}

int main() {
    
    int i, n;
    string *A;

    if( legge(&A, &n)) return 1;

    srand(time(NULL));
    quicksort(A, 0, n-1);
    
    /* Stampa l'array ordinato */
    for( i = 0; i < n; i++ ) 
        printf("%s\n", A[i]);
        
    return 0;
}
