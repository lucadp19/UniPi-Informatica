#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "lib.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "There must be exactly one additional argument: the waiting time in seconds.");
        exit(EXIT_FAILURE);
    }

    int X;
    if( (X = isNumber(argv[1])) < 0){
        fprintf(stderr, "The additional argument must be a postive integer.");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int status;

    if( (pid = fork()) == -1){
        perror("main: fork");
        exit(EXIT_FAILURE);
    }

    if(pid){ // father
        waitpid(pid, &status, 0);
        if( WIFEXITED(status) ){
            printf("Wait is finished!\n");
        }
    } else { // child
        execlp("/bin/sleep", "sleep", argv[1], (char*)NULL);
        perror("main: execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}