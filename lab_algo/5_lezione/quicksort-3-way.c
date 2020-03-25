#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void swap(int* a, int* b){
    int tmp = *a;
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
void distribuzione(int a[], int sx, int px, int dx, int* less, int* greater) { 
    int pivot = a[px];
    int i = sx - 1;
    int j = sx;
    int k = dx;

    swap(&a[px], &a[dx]);
    px = dx;

    while(j < k) {
        if(a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
            j++;
        }
        else if (a[j] > pivot) {
            k--;
            swap(&a[j], &a[k]);
        }
        else j++;
    }
    
    swap(&a[dx], &a[j]);
    *less = i;
    *greater = j + 1;
}

void quicksort( int a[], int sx, int dx ) {
    int pivot;
    int less, greater;
    if( sx < dx ) {
        // printf("\nArray: ");
        // for(int i = sx; i <= dx; i++)
        //     printf("%d ", a[i]);
        
        /* DA IMPLEMENTARE: scelta del pivot. Scegliere una posizione a caso tra sx e dx inclusi. */
        pivot = rand()%(dx - sx + 1) + sx;

        // printf("\nPivot: %d Value: %d\n", pivot, a[pivot]);

        distribuzione(a, sx, pivot, dx, &less, &greater); /* separa gli elementi minori di a[pivot] 
                                da quelli maggiori o uguali */

        // printf("%d %d\nLess: ", less, greater);
        // for(int i = sx; i <= less; i++)
        //     printf("%d ", a[i]);
        // printf("\nEqual: ");
        // for(int i = less + 1; i < greater; i++)
        //     printf("%d ", a[i]);
        // printf("\nGreater: ");
        // for(int i = greater; i <= dx; i++)
        //     printf("%d ", a[i]);
        // printf("\n");

        /* Ordina ricorsivamente le due metà */
        quicksort(a, sx, less);
        quicksort(a, greater, dx);
    
    }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(int **a, int *len) {

  int i;
  scanf("%d", len);
  if(*len <= 0) return 1;

  *a = (int *) malloc(*len * sizeof(int));
  if(*a == NULL) return 1;

  for( i = 0; i < *len; i++ ) 
	  scanf("%d", (*a)+i);
  
  return 0;

}

int main() {
  
  int i, n, *A;

  if( legge(&A, &n)) return 1;

  srand(time(NULL));
  quicksort(A, 0, n-1);
  
  /* Stampa l'array ordinato */
  for( i = 0; i < n; i++ ) 
    printf("%d ", A[i]);
	
  return 0;
}
