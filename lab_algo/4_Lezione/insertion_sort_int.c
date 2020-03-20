#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int a[], int len);
void swap(int* a, int* b);

int main(){
    int N;
    int *a;

    scanf("%d", &N);
    a = (int*) malloc(N*sizeof(int));

    for(int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    
    insertion_sort(a, N);

    for(int i = 0; i < N; i++)
        printf("%d\n", a[i]);
    
    free(a);
    return 0;
}

void insertion_sort(int a[], int len){
    int j;
    for(int i = 1; i < len; i++){
        j = i;
        while(j > 0 && a[j] < a[j-1]){
            swap(&a[j], &a[j-1]);
            j--;
        }
    }
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}