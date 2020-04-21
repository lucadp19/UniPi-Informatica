#include <stdio.h>
#include <stdlib.h>

int* read_array(int len);
int max_subarray(int a[], int len);

int main(){
    int N;
    int *a;

    scanf("%d", &N);
    a = read_array(N);

    printf("%d\n", max_subarray(a, N));
    free(a);
    return 0;
}

int* read_array(int len){
    int* array = malloc(len*sizeof(int));
    if(array == NULL)
        return NULL;
    
    for(int i = 0; i < len; i++)
        scanf("%d", &array[i]);

    return array;
}

int max_subarray(int a[], int len){
    int sum = 0;
    int max = 0;

    for(int i = 0; i < len; i++){
        if(sum > 0) sum+=a[i];
        else sum = a[i];

        if(sum > max) max = sum;
    }

    return max;
}