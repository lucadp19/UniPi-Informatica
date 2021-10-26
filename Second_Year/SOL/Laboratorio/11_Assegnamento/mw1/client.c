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
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
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
    // sending strings to server
    char buf[BUFSIZE];
    while(true){
        printf("Input new string or \"quit\": ");
        memset(buf, '\0', BUFSIZE);
        CHECK_NOT_EQ(fgets(buf, BUFSIZE, stdin), NULL, "error fgets");
        if(strncmp(buf, "quit", 4) == 0)
            break;

        int len = strlen(buf);
        
        // must send calculation to server
        CHECK_NOT_EQ( writen(fd_sock, &len, sizeof(int)), -1, "error writing" );
        CHECK_NOT_EQ( writen(fd_sock, buf, len*sizeof(char)), -1, "error writing" );

        // reading answer
        memset(buf, '\0', BUFSIZE);
        CHECK_NOT_EQ( readn(fd_sock, &len, sizeof(int)), -1, "error reading" );
        CHECK_NOT_EQ( readn(fd_sock, buf, len*sizeof(char)), -1, "error reading" );

        buf[len] = '\0';
        fprintf(stdout, "Answer: %s\n", buf);
    }

    close(fd_sock);
    return 0;
}