#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    int fd_src, fd_dest;
    SAFE_OPEN(fd_dest, dest, O_WRONLY);
    SAFE_OPEN(fd_src, src, O_RDONLY);

    // reading and writing
    int lung;
    while((lung = read(fd_src, buf, buf_size)) > 0){
        // writes on fd_dest, but if write result is -1 exits
        CHECK_NOTEQ(
            (write(fd_dest, buf, buf_size)),
            -1,
            "Error while writing in file"
        );
    }
    CHECK_NOTEQ(lung, -1, "Error while reading file");

    // closing files and freeing memory
    SAFE_CLOSE(fd_src);
    SAFE_CLOSE(fd_dest);
    free(buf);
    
    return 0;
}