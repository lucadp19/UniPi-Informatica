#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "lib.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "There must be exactly one additional argument: the number of zombie processes to be created.");
        exit(EXIT_FAILURE);
    }

    int N;
    if( (N = isNumber(argv[1])) < 0){
        fprintf(stderr, "The additional argument must be a postive integer.");
        exit(EXIT_FAILURE);
    }    

    for (int i = 0; i < N; i++) {
        pid_t pid;
        // int status;
        if( (pid = fork()) == -1){
            perror("main: fork");
            exit(EXIT_FAILURE);
        }

        if(!pid) { // child
            exit(EXIT_SUCCESS);
        }
    }

    sleep(15);
    return 0;
}
