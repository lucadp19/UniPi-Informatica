#define _POSIX_C_SOURCE 200112L

#include "tokenizer.h"
#include <string.h>
#include <stdio.h>

void tokenizer(char *string){
    char* token = strtok(string, " ");
    while (token){
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}

void tokenizer_r(char *string){
    char *save;
    char *token = strtok_r(string, " ", &save);
    while (token){
        printf("%s\n", token);
        token = strtok_r(NULL, " ", &save);
    }
}