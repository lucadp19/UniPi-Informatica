#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

int abs(int n){
    if(n < 0) return -n;
    else return n;
}

int min(int a, int b){
    if(a < b) return a;
    else return b;
}
int min_3(int a, int b, int c){
    if(a < b && b < c) return a;
    else if(b < a && b < c) return b;
    else return c;
}

int max(int a, int b){
    if(a > b) return a;
    else return b;
}
int max_3(int a, int b, int c){
    if(a > b && b > c) return a;
    else if(b > a && b > c) return b;
    else return c;
}


/* QSORT COMPARE FUNCTIONS */

int int_cmp_increasing(const void* a, const void* b){
    int n = *((int*) a);
    int m = *((int*) b);
    return n - m;
}
int int_cmp_decreasing(const void* a, const void* b){
    int n = *((int*) a);
    int m = *((int*) b);
    return m - n;
}

int str_cmp_increasing(const void* a, const void* b){
    return strcmp(*((string*) a), *((string*) b));
}
int str_cmp_decreasing(const void* a, const void* b){
    return -strcmp(*((string*) a), *((string*) b));
}


