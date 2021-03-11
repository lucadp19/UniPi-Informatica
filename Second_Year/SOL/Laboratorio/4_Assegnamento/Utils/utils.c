#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -2;
}