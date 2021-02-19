#include <stdio.h>

int* FindVal(int A[], int len, int val);

int main(){
    int A[10];
    int val;
    for(int i = 0; i < 10; i++)
        scanf("%d", &A[i]);
    scanf("%d", &val);
    if(FindVal(A, 10, val) != NULL)
        printf("trovato\n");
    else
        printf("non trovato\n");
    
    return 0;
}

int* FindVal(int A[], int len, int val){
    for(int i = 0; i < len; i++){
        if(A[i] == val)
            return &A[i];
    }
    return NULL;
}