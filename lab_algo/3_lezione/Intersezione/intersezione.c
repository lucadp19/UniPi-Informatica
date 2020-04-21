#include <stdio.h>
#include <stdlib.h>

int* read_array(int len);
int intersection(int a[], int len_a, int b[], int len_b);
int found_element(int elem, int a[], int len);

int main(){
    int N, M;
    int *a, *b;

    scanf("%d", &N);
    a = read_array(N);

    scanf("%d", &M);
    b = read_array(M);

    printf("%d\n", intersection(a, N, b, M));
    free(a);
    free(b);
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

int intersection(int a[], int len_a, int b[], int len_b){
    int count = 0;
    for(int i = 0; i < len_a; i++)
        count += found_element(a[i], b, len_b);
    return count;
}

int found_element(int elem, int a[], int len){
    int i = 0;
    while(i < len){
        if(a[i] == elem)
            return 1;
        i++;
    }
    return 0;
}