#include <stdio.h>

void primoultimopari(int[], int, int*, int*);

int main(){
    int i;
    int arr[7];
    const int dim = 7;
    int prima = -1;
    int ultima = -1;

    for(i = 0; i < dim; i++)
        scanf("%d", &arr[i]);
    primoultimopari(arr, dim, &prima, &ultima);
    printf("%d %d\n", prima, ultima);
    return 0;
}

void primoultimopari(int arr[], int dim, int* prima, int* ultima){
    int i;
    for(i = 0; i < dim; i++){
        if(*(arr+i)%2 == 0){
            *ultima = i;
            if(*prima == -1)
                *prima = i;
        }
    }
}
