#include <stdio.h>
#include <stdlib.h>

long isNumber(const char* s);
int somma(int x);

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "There must be exactly two arguments");
    }

    long N = isNumber(argv[1]);
    if(N <= 0){
        fprintf(stderr, "The second argument must be a positive integer");
        return -1;
    }

    printf("Please enter the %d numbers.\n", N);
    for(int i = 0; i < N; i++){
        int x;
        scanf("%d", &x);
        printf(" >>> Sum: %d\n", somma(x));
    }

    return 0;
}

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -1;
}

int somma(int x){
    static int sum = INIT_VALUE;
    sum += x;
    return sum;
}