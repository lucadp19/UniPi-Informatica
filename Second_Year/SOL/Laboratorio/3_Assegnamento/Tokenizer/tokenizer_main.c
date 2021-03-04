#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib/tokenizer.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        fprintf(stderr, "This program needs exactly one string argument.");
        return -1;
    }

    size_t len = strlen(argv[1]) + 1;
    char* argv_copy = malloc(len * sizeof(char));
    strncpy(argv_copy, argv[1], len);

    printf("\ttokenizer\n");
    tokenizer(argv_copy);

    strncpy(argv_copy, argv[1], len);

    printf("\ttokenizer_r:\n");
    tokenizer_r(argv_copy);

    return 0;
}