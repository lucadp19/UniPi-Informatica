#include <stdio.h>

int last_column(int[][3], int);

int main(){
    int matrix[4][3];
    int rows = 4;
    int cols = 3;
    int i, j;

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);

    printf("%d\n", last_column(matrix, rows));
    return 0;
}

int last_column(int mat[][3], int n){
    int last = -1; // ultima colonna che soddisfa la condizione
    int i, j;
    int m = 3; // numero di colonne

    for(j = 0; j < m; j++){
        int all_multiples = 1; 
        /* all_multiples vale 1 se tutti i numeri incontrati nella colonna sono multipli di 3
         * 0 altrimenti */
        i = 0;
        while(all_multiples && i < n){
            if(mat[i][j]%3 == 0)
                i++;
            else
                all_multiples = 0; // se troviamo un numero non multiplo di 3 usciamo dal ciclo
        }
        if(all_multiples)
            last = j;
    }
    
    return last;
}
