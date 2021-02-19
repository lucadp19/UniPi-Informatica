#include <stdio.h>

void minmax(int A[], int dim, int* min, int* max);

int main(){
    int A[10];
    int min, max;
    for(int i = 0; i < 10; i++)
        scanf("%d", &A[i]);
    minmax(A, 10, &min, &max);
    printf("%d\n%d\n%d\n%d\n", min, A[min], max, A[max]);
    return 0;
}

void minmax(int A[], int dim, int* min, int* max){
    *min = 0;
    *max = 0;
    for(int i = 1; i < dim; i++){
        if(A[i] < A[*min])
            *min = i;
        if(A[i] > A[*max])
            *max = i;
    }
}