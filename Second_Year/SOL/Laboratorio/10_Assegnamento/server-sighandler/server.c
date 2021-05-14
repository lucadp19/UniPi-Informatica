#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <errno.h> 
#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "conn.h"

#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108

typedef struct {
    int len;
    char* str;
} msg_t;

static volatile sig_atomic_t terminate = 0;
void sig_handler(int useless){
    terminate = 1;
}

void to_upper(char* str, size_t len){
    if(str == NULL) return;

    char* ptr = str;
    int k = 0;
    while(k < len && *ptr != '\0'){
        if(islower(*ptr))
            *ptr = toupper(*ptr);
        ptr++;
        k++;
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

        to_upper(msg.str, msg.len);

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

        free(msg.str);
    } while(1);
    close(fd_client);
    fprintf(stdout, "Connection closed!\n");
    fflush(stdout);
    return NULL;
}

int spawn_thread(long fd_client){
    pthread_attr_t thread_attr;
    pthread_t t_id;
    
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGPIPE);

    if(pthread_sigmask(SIG_BLOCK, &mask, &oldmask) != 0) {
        fprintf(stderr, "Error in pthread_sigmask.\n");
        exit(EXIT_FAILURE);
    }

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
    
    if(pthread_sigmask(SIG_SETMASK, &oldmask, NULL) != 0) {
        fprintf(stderr, "Error in pthread_sigmask.\n");
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

    // --------------- SIGNALS --------------- //
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGPIPE);

    if(pthread_sigmask(SIG_BLOCK, &mask, &oldmask) != 0) {
        fprintf(stderr, "Error in pthread_sigmask.\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction siga;
    memset(&siga, 0, sizeof(siga));
    siga.sa_handler = sig_handler;
    CHECK_NOT_EQ(sigaction(SIGINT, &siga, NULL), -1, "sigaction SIGINT");
    CHECK_NOT_EQ(sigaction(SIGQUIT, &siga, NULL), -1, "sigaction SIGQUIT");
    CHECK_NOT_EQ(sigaction(SIGTERM, &siga, NULL), -1, "sigaction SIGTERM");
    CHECK_NOT_EQ(sigaction(SIGHUP, &siga, NULL), -1, "sigaction SIGHUP");

    siga.sa_handler = SIG_IGN;
    CHECK_NOT_EQ(sigaction(SIGPIPE, &siga, NULL), -1, "sigaction SIGPIPE");

    if(pthread_sigmask(SIG_SETMASK, &oldmask, NULL) != 0) {
        fprintf(stderr, "Error in pthread_sigmask.\n");
        exit(EXIT_FAILURE);
    }    

    // ---------------- SOCKETS ---------------- //
    int fd_sock;
    CHECK_NOT_EQ(fd_sock = socket(AF_UNIX, SOCK_STREAM, 0), -1, "socket server");

    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;

    CHECK_NOT_EQ( bind(fd_sock, (struct sockaddr*)&sa, sizeof(sa)), -1, "bind server" );
    CHECK_NOT_EQ( listen(fd_sock, 1), -1, "listen server" );

    while(!terminate){
        long fd_client = -1;
        printf("Waiting for client connection...\n");
        if(!terminate && (fd_client = accept(fd_sock, NULL, 0)) == -1){
            if (errno == EINTR){
                if(terminate) break;
                else {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
            }
        }
        printf("Connected!\n");

        if(spawn_thread(fd_client) < 0){
            exit(EXIT_FAILURE);
        }
    }
    close(fd_sock);
    return 0;
}
