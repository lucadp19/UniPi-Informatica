#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_search(char **a, int sx, int dx, char* string);

int main(){
    int N, cont;
    char **a;

    scanf("%d", &N);
    a = (char**) malloc(N * sizeof(char*));

    for(int i = 0; i < N; i++){
        a[i] = (char*) malloc(101 * sizeof(char));
        scanf("%s", a[i]);
    }
    
    scanf("%d", &cont);
    while(cont){
        char string[101];
        scanf("%s", string);
        printf("%d\n", binary_search(a, 0, N-1, string));
        scanf("%d", &cont);
    }

    for(int i = 0; i < N; i++)
        free(a[i]);
    free(a);
    return 0;
}

int binary_search(char **a, int sx, int dx, char* string){
    if(sx > dx) return -1;
    if(sx == dx){
        if(strcmp(a[sx], string) == 0) return sx;
        else return -1;
    }

    int cx = (sx + dx)/2;
    int cmp = strcmp(a[cx], string);
    if(cmp == 0) return cx;
    else if (cmp > 0) return binary_search(a, sx, cx-1, string);
    else return binary_search(a, cx+1, dx, string);
}