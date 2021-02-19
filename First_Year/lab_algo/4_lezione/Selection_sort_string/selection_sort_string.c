#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selection_sort(char **a, int len);

int main(){
    int N;
    char **a;

    scanf("%d", &N);
    a = (char**) malloc(N * sizeof(char*));

    for(int i = 0; i < N; i++){
        a[i] = (char*) malloc(101 * sizeof(char));
        scanf("%s", a[i]);
    }
    
    selection_sort(a, N);

    for(int i = 0; i < N; i++){
        printf("%s\n", a[i]);
        free(a[i]);
    }
    
    free(a);
    return 0;
}

void selection_sort(char **a, int len){
    int pos_min;
    char* tmp;
    for(int i = 0; i < len; i++){
        pos_min = i;
        for(int j = i+1; j < len; j++){
            if(strcmp(a[j], a[pos_min]) < 0)
                pos_min = j;
        }
        if(pos_min != i){
            tmp = a[pos_min];
            a[pos_min] = a[i];
            a[i] = tmp;
        }
    }
}