#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <errno.h> 
#include <unistd.h>

#include "lib.h"
#include "conn.h"

#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108

void to_upper(char* str){
    char* ptr = str;
    while(*ptr != '\0'){
        if(islower(*ptr))
            *ptr = toupper(*ptr);
        ptr++;
    } 
}

void* thread_fun(void* arg){
    if(arg == NULL){
        exit(EXIT_FAILURE);
    }

    long fd_client = (long)arg;
    do {
        msg_t msg;
        int l;
        if( (l = readn(fd_client, &msg.len, sizeof(int))) == -1){
            perror("first read");
            break;
        }
        if(l == 0) break;

        msg.str = calloc(msg.len, sizeof(char));
        if(msg.str == NULL){
            perror("calloc"); break;
        }

        if( (l = readn(fd_client, msg.str, msg.len * sizeof(char))) == -1){
            perror("second read");
            free(msg.str);
            break;
        }

        to_upper(msg.str);

        if( (l = writen(fd_client, &msg.len, sizeof(int))) == -1){
            perror("first write");
            free(msg.str);
            break;
        }

        if( (l = writen(fd_client, msg.str, msg.len * sizeof(char))) == -1){
            perror("second write");
            free(msg.str);
            break;
        }
    } while(1);
    close(fd_client);
    fprintf(stdout, "Connection closed!\n");
    fflush(stdout);
    return NULL;
}

int spawn_thread(long fd_client){
    pthread_attr_t thread_attr;
    pthread_t t_id;
       
    if(pthread_attr_init(&thread_attr) != 0){
        fprintf(stderr, "pthread_attr_init failed\n");
        close(fd_client);
        return -1;
    }
    if(pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0){
        fprintf(stderr, "pthread_attr_setdetachstate failed\n");
        close(fd_client);
        return -1;
    }
    if(pthread_create(&t_id, &thread_attr, thread_fun, (void*)fd_client) != 0){
        fprintf(stderr, "pthread_create failed\n");
        close(fd_client);
        return -1;
    }

    return 0;
}


void cleanup(){
    unlink(SOCKNAME);
}

int main(){
    cleanup();
    atexit(cleanup);

    // ---------------- SOCKETS ---------------- //
    int fd_sock;
    CHECK_NOT_EQ(fd_sock = socket(AF_UNIX, SOCK_STREAM, 0), -1, "socket server");

    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;

    CHECK_NOT_EQ( bind(fd_sock, (struct sockaddr*)&sa, sizeof(sa)), -1, "bind server" );
    CHECK_NOT_EQ( listen(fd_sock, 1), -1, "listen server" );

    while(true){
        long fd_client = -1;
        printf("Waiting for client connection...\n");
        if((fd_client = accept(fd_sock, NULL, 0)) == -1){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connected!\n");

        if(spawn_thread(fd_client) < 0){
            exit(EXIT_FAILURE);
        }
    }
    close(fd_sock);
    return 0;
}
