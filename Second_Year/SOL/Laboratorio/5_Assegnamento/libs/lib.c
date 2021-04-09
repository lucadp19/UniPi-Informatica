#include "lib.h"

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -2;
}

void* safe_malloc(size_t size){
    void* ptr;
    if((ptr = malloc(size)) == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}