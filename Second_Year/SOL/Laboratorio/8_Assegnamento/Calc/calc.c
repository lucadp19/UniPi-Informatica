#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "lib.h"

#define BUFFSIZE 256

int bc_call(char* op, char* res){
    int to_bc_pipe[2];
    int from_bc_pipe[2];

    CHECK_NOT_EQ(pipe(to_bc_pipe), -1, "Error while creating input pipe");
    CHECK_NOT_EQ(pipe(from_bc_pipe), -1, "Error while creating output pipe");

    int pid;
    CHECK_NOT_EQ((pid = fork()), -1, "Fork failed");

    if (pid == 0) { // child process
        // closing pipes
        CHECK_NOT_EQ(close(to_bc_pipe[1]), -1, "Error closing pipe descriptor");
        CHECK_NOT_EQ(close(from_bc_pipe[0]), -1, "Error closing pipe descriptor");

        // redirecting input and output
        CHECK_NOT_EQ(dup2(to_bc_pipe[0], 0), -1, "Error dup2 stdin");
        CHECK_NOT_EQ(dup2(from_bc_pipe[1], 1), -1, "Error dup2 stdout");
        CHECK_NOT_EQ(dup2(from_bc_pipe[1], 2), -1, "Error dup2 stderr");

        execl("/usr/bin/bc", "bc", "-lq", (char*)NULL);
        // execl failed
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    // parent process
    // closing pipes
    CHECK_NOT_EQ(close(to_bc_pipe[0]), -1, "Error closing pipe descriptor");
    CHECK_NOT_EQ(close(from_bc_pipe[1]), -1, "Error closing pipe descriptor");

    int len;
    CHECK_NOT_EQ(write(to_bc_pipe[1], op, BUFFSIZE), -1, "Error writing to pipe");
    CHECK_NOT_EQ((len = read(from_bc_pipe[0], res, BUFFSIZE)), -1, "Error reading from pipe");

    // closing things
    CHECK_NOT_EQ(close(to_bc_pipe[1]), -1, "Error closing pipe");
    CHECK_NOT_EQ(waitpid(pid, NULL, 0), -1, "Error closing child process");

    return len;
}

void to_zero(char* str, size_t size){
    for(int i = 0; i < size; i++)
        str[i] = 0;
}

int main(){
    while(true){
        char operation[BUFFSIZE];
        char result[BUFFSIZE];

        to_zero(operation, BUFFSIZE);

        printf("Operation: ");
        if(fgets(operation, BUFFSIZE, stdin) == NULL){
            perror("Error while reading from stdin");
            exit(EXIT_FAILURE);
        }

        if(strncmp(operation, "quit", 4) == 0)
            break;
        
        int len = bc_call(operation, result);
        result[len] = '\0';
        
        printf("Result: %s", result);
    }
    printf("Exiting!\n");
}