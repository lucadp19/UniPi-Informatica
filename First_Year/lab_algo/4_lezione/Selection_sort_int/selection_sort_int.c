#include <stdio.h>
#include <stdlib.h>

void selection_sort(int a[], int len);

int main(){
    int N;
    int *a;

    scanf("%d", &N);
    a = (int*) malloc(N*sizeof(int));

    for(int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    
    selection_sort(a, N);

    for(int i = 0; i < N; i++)
        printf("%d\n", a[i]);
    
    free(a);
    return 0;
}

void selection_sort(int a[], int len){
    int pos_min;
    int tmp;
    for(int i = 0; i < len; i++){
        pos_min = i;
        for(int j = i+1; j < len; j++){
            if(a[j] < a[pos_min])
                pos_min = j;
        }
        if(pos_min != i){
            tmp = a[pos_min];
            a[pos_min] = a[i];
            a[i] = tmp;
        }
    }
}