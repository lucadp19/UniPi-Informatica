#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

#define DEFAULT_BUF_SIZE 256

int main(int argc, char* argv[]){
    if(argc < 3)
        ERROR_EXIT("There must be at least 2 additional arguments.");
    if(argc > 4)
        ERROR_EXIT("There can be at most 3 additional arguments.");

    char* dest = argv[1];
    char* src  = argv[2];
    int buf_size = DEFAULT_BUF_SIZE;
    if(argc == 4 && (buf_size = isNumber(argv[3])) < 0)
        ERROR_EXIT("The third argument must be a positive integer, representing the size of the buffer.");
    
    char* buf = safe_malloc(buf_size);
    
    // opening files
    FILE *file_src, *file_dest;
    SAFE_FOPEN(file_dest, dest, "w");
    SAFE_FOPEN(file_src, src, "r");

    // reading and writing
    while(fgets(buf, buf_size, file_src) != NULL){
       fprintf(file_dest, buf);
    }

    // closing files
    SAFE_FCLOSE(file_src);
    SAFE_FCLOSE(file_dest);
    free(buf);
    
    return 0;
}
