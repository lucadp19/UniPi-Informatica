#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void reverse(int A[], int N);

int main(){
    int N;
    int* A;

    scanf("%d", &N);
    A = malloc(N*sizeof(int));

    for(int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    
    reverse(A, N);

    for(int i = 0; i < N; i++)
        printf("%d", A[i]);

    free(A);
    return 0;
}

void reverse(int A[], int N){
    int tmp;
    int half = floor(N/2);
    for(int i = 0; i < half; i++){
        tmp = A[N-i-1];
        A[N-i-1] = A[i];
        A[i] = tmp;
    }
}