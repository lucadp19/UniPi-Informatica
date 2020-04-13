#include <stdio.h>
#include <stdlib.h>

int abs(int n){
    if(n < 0)
        return -n;
    else
        return n;
}

int cmp(const void* a, const void* b){
    int n = *((int*) a);
    int m = *((int*) b);
    if(abs(n)%2 != abs(m)%2){
        return abs(n)%2 - abs(m)%2;
    } else if (n%2 == 0){
        return n - m;
    } else 
        return m - n;
}

int main(){
    int N;
    int* a;

    scanf("%d", &N);
    a = (int*) malloc(N*sizeof(int));

    for(int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    qsort(a, N, sizeof(int), cmp);

    for(int i = 0; i < N; i++)
        printf("%d\n", a[i]);

    free(a);

    return 0;
}