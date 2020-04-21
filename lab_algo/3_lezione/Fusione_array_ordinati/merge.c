#include <stdio.h>
#include <stdlib.h>

int* read_array(int len);
int* merge(int a[], int len_a, int b[], int len_b);

int main(){
    int N, M;
    int *a, *b, *c;

    scanf("%d", &N);
    a = read_array(N);

    scanf("%d", &M);
    b = read_array(M);

    c = merge(a, N, b, M);

    // for(int i = 0; i < N; i++)
    //     printf("%d\n", a[i]);
    // printf("\n\n");

    // for(int i = 0; i < M; i++)
    //     printf("%d\n", b[i]);
    // printf("\n\n");

    for(int i = 0; i < N+M; i++)
        printf("%d\n", c[i]);
    // printf("%d", N+M);

    free(a);
    free(b);
    free(c);
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

int* merge(int a[], int len_a, int b[], int len_b){
    int len = len_a + len_b;
    int *dest = malloc(len*sizeof(int));
    int i = 0;
    int j = 0;

    for(int k = 0; k < len; k++){
        if(i >= len_a)
            dest[k] = b[j++];
        else if(j >= len_b)
            dest[k] = a[i++];
        else if(b[j] < a[i])
            dest[k] = b[j++];
        else 
            dest[k] = a[i++];
    }
    
    return dest;
}
