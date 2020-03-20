#include <stdio.h>

void matr_sum(int[][3], int[][3], int[][3], int);

int main(){
    int i, j;
    const int rows = 4;
    const int cols = 3;
    int A[4][3];
    int B[4][3];
    int C[4][3];

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            scanf("%d", &A[i][j]);
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            scanf("%d", &B[i][j]);

    matr_sum(A, B, C, rows);

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
}

void matr_sum(int A[][3], int B[][3], int C[][3], int rows){
    int cols = 3;
    int i, j;

    for(i = 0; i < rows; i++)
        for(j = 0; j < rows; j++)
            C[i][j] = A[i][j] + B[i][j];
}
