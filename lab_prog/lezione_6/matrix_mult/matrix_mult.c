#include <stdio.h>

void multiplymatr(int a[][2], int b[][3], int c[][3], const int a_r); 

int main(){
    // int a[4][2], b[2][3], c[4][3];
    int i, j;

    const int a_r = 4;  // n.righe di a
    const int a_c = 2;  // n.colonne di b
    const int b_r = 2;  // n.righe di b
    const int b_c = 3;  // n.colonne di b
    const int c_r = 4;  // n.righe di c
    const int c_c = 3;  // n.colonne di c
    int a[a_r][a_c], b[b_r][b_c], c[c_r][c_c];

    for(i = 0; i < a_r; i++)
        for(j = 0; j < a_c; j++)
            scanf("%d", &a[i][j]);

    for(i = 0; i < b_r; i++)
        for(j = 0; j < b_c; j++)
            scanf("%d", &b[i][j]);
    
    multiplymatr(a, b, c, a_r);

    for(i = 0; i < c_r; i++){
        for(j = 0; j < c_c; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}

void multiplymatr(int a[][2], int b[][3], int c[][3], const int a_r){
    const int a_c = 2;
    const int b_c = 3; 
    int i, j, k;

    for(i = 0; i < a_r; i++){               // per ogni riga di a
        for(j = 0; j < b_c; j++){           // prendo ogni colonna di b
            int sum = 0;
            for(k = 0; k < a_c; k++)        // non funziona se a_c != b_r         
                sum += a[i][k]*b[k][j];
            c[i][j] = sum;
        }
    }
}
