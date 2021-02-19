#include <stdio.h>

void multipli(int, int);

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    multipli(N, M);
    return 0;
}

void multipli(int N, int M){
    int i = 1;
    for(; i*M <= N; i++)
        printf("%d\n", i*M);
}
