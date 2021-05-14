#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h> 
#include <unistd.h>

#include "lib.h"
#include "conn.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108

int main(){
    int fd_sock;
    CHECK_NOT_EQ(fd_sock = socket(AF_UNIX, SOCK_STREAM, 0), -1, "socket client");

    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, strlen(SOCKNAME)+1);
    sa.sun_family = AF_UNIX;
    
    printf("Waiting for server connection...\n");
    while( (connect(fd_sock, (struct sockaddr*)&sa, sizeof(sa))) == -1){
        if(errno == ENOENT) // there is no server yet
            sleep(1);
        else {
            perror("socket client connect");
            exit(EXIT_FAILURE);
        }
    }

    printf("Connected!\n");

    msg_t msg;
    CHECK_NOT_EQ( msg.str = malloc(BUFSIZE*sizeof(char)), NULL, "malloc");

    // sending calculations to server
    while(true){
        printf("Input new calculation or \"quit\": ");
        memset(msg.str, '\0', BUFSIZE);
        CHECK_NOT_EQ(fgets(msg.str, BUFSIZE-1, stdin), NULL, "error fgets");
        if(strncmp(msg.str, "quit", 4) == 0)
            break;
        
        msg.len = strlen(msg.str);

        // must send calculation to server
        CHECK_NOT_EQ( writen(fd_sock, &msg.len, sizeof(int)), -1, "error writing" );
        CHECK_NOT_EQ( writen(fd_sock, msg.str, msg.len*sizeof(char)), -1, "error writing" );

        // reading answer
        int l;
        char buf[BUFSIZE];
        memset(buf, '\0', BUFSIZE);
        CHECK_NOT_EQ( readn(fd_sock, &l, sizeof(int)), -1, "read");
        CHECK_NOT_EQ( readn(fd_sock, buf, l), -1, "read");

        buf[l] = '\0';
        fprintf(stdout, "Answer: %s\n", buf);
    }

    if(msg.str) free(msg.str);

    close(fd_sock);
    return 0;
}