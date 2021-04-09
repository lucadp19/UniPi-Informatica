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

    int N;
    if( (N = isNumber(argv[1])) < 0){
        fprintf(stderr, "The additional argument must be a postive integer.");
        exit(EXIT_FAILURE);
    }
  
    while(N > 0) {
        pid_t pid;
        int status;

        for(int i = 0; i < N; i++)
            printf("-");
        printf(" %d: creo un processo figlio\n", getpid());
        fflush(stdout);

        if( (pid = fork()) == -1){
            perror("main: fork");
            exit(EXIT_FAILURE);
        }

        if(pid){ // father
            waitpid(pid, &status, 0);
            if( WIFEXITED(status) ){
                for(int i = 0; i < N; i++)
                    printf("-");
                printf(" %d: terminato con successo\n", getpid());
                fflush(stdout);
            }
            break;
        } else { // child
            N--;
            continue;
        }
    }
    
    if(N == 0){
        printf("%d: sono l'ultimo discendente\n", getpid());
        printf("%d: terminato con successo\n", getpid());
        exit(EXIT_SUCCESS);
    }
    return 0;
}
