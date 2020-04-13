#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

int cmp(const void* a, const void* b){
    return -strcmp(*((string*) a), *((string*) b));
}

int main(){
    int N;
    string* a;

    scanf("%d", &N);
    a = (string*) malloc(N*sizeof(string));

    for(int i = 0; i < N; i++){
        a[i] = (string) malloc(101*sizeof(char));
        scanf("%s", a[i]);
    }

    qsort(a, N, sizeof(string), cmp);

    for(int i = 0; i < N; i++){
        printf("%s\n", a[i]);
        free(a[i]);
    }

    free(a);

    return 0;
}