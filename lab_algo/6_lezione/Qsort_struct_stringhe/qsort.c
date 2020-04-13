#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct {
    string str;
    int len;
} stringL;

int cmp(const void* a, const void* b){
    stringL* s1 = (stringL*) a;
    stringL* s2 = (stringL*) b;

    if(s1->len == s2->len)
        return strcmp(s1->str, s2->str);
    else return s1->len - s2->len;
}

int main(){
    int N;
    stringL* a;

    scanf("%d", &N);
    a = (stringL*) malloc(N*sizeof(stringL));

    for(int i = 0; i < N; i++){
        a[i].str = (string) malloc(101*sizeof(char));
        scanf("%s", a[i].str);
        a[i].len = strlen(a[i].str);
    }

    qsort(a, N, sizeof(stringL), cmp);

    for(int i = 0; i < N; i++){
        printf("%s\n", a[i].str);
        free(a[i].str);
    }

    free(a);

    return 0;
}