#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h> 
#include <unistd.h>

#include "lib.h"
#include "conn.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108

int bc_call(const char op[], char* res){
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

        execl("/usr/bin/bc", "bc", "-l", (char*)NULL);
        // execl failed
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    // parent process
    // closing pipes
    CHECK_NOT_EQ(close(to_bc_pipe[0]), -1, "Error closing pipe descriptor");
    CHECK_NOT_EQ(close(from_bc_pipe[1]), -1, "Error closing pipe descriptor");

    int len;
    CHECK_NOT_EQ(write(to_bc_pipe[1], (char*)op, strlen(op)), -1, "Error writing to pipe");
    CHECK_NOT_EQ((len = read(from_bc_pipe[0], res, BUFSIZE)), -1, "Error reading from pipe");

    // closing things
    CHECK_NOT_EQ(close(to_bc_pipe[1]), -1, "Error closing pipe");
    CHECK_NOT_EQ(waitpid(pid, NULL, 0), -1, "Error closing child process");

    return len;
}

void cleanup(){
    unlink(SOCKNAME);
}

int main(){
    cleanup();
    atexit(cleanup);

    int fd_sock, fd_client;
    CHECK_NOT_EQ(fd_sock = socket(AF_UNIX, SOCK_STREAM, 0), -1, "socket server");

    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;

    CHECK_NOT_EQ( bind(fd_sock, (struct sockaddr*)&sa, sizeof(sa)), -1, "bind server" );
    CHECK_NOT_EQ( listen(fd_sock, 1), -1, "listen server" );

    char cont;
    do{
        printf("Waiting for client connection...\n");
        CHECK_NOT_EQ( fd_client = accept(fd_sock, NULL, NULL), -1, "accept server" );
        printf("Connected!\n");

        msg_t msg;
        CHECK_NOT_EQ( msg.str = malloc(BUFSIZE*sizeof(char)), NULL, "malloc");
        
        while(true){
            int l, res_len;
            char res[BUFSIZE];

            memset(msg.str, '\0', BUFSIZE);

            CHECK_NOT_EQ( l=readn(fd_client, &msg.len, sizeof(int)), -1, "error read1");
            CHECK_NOT_EQ( l=readn(fd_client, msg.str, msg.len * sizeof(char)), -1, "error read2");

            if(l == 0) break;

            // calculating result
            memset(res, '\0', BUFSIZE);
            CHECK_NOT_EQ(res_len = bc_call(msg.str, res), -1, "error bc call");
            res[res_len] = '\0';

            // writing result back on socket
            CHECK_NOT_EQ( writen(fd_client, &res_len, sizeof(int)), -1, "error write");
            CHECK_NOT_EQ( writen(fd_client, res, res_len*sizeof(char)), -1, "error write");
        }
        if(msg.str) free(msg.str);

        close(fd_client);
        printf("Connection closed. Do you want to continue? (y/n)\n");
        scanf(" %c", &cont);
    } while(cont == 'y');

    close(fd_sock);
    return 0;
}
