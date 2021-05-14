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
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108
#define R_ENDP 0
#define W_ENDP 1

typedef struct {
    int len;
    char* str;
} msg_t;

typedef struct {
    sigset_t* set;
    int* pipe;
} sigh_arg_t;

static bool terminate = false;

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

void* sighandler(void* arg){
    sigh_arg_t* sigh_arg = (sigh_arg_t*)arg;
    sigset_t* set_ptr = sigh_arg->set;
    int* pipe = sigh_arg->pipe;

    while(true){
        int sig;
        int err = sigwait(set_ptr, &sig);
        if(err != 0){
            errno = err;
            perror("sigwait error");
            return NULL;
        }

        switch (sig) {
            case SIGINT:
            case SIGTERM:
            case SIGQUIT:
                terminate = true;
                printf("\nRecieved signal, closing server!\n");
                fflush(stdout);
                CHECK_NOT_EQ( close(pipe[W_ENDP]), -1, "close pipe");
                return NULL;
            
            default: ;
        }
    }
    return NULL;
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

    // --------------- SIGNALS --------------- //
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);

    if(pthread_sigmask(SIG_BLOCK, &mask, NULL) != 0) {
        fprintf(stderr, "Error in pthread_sigmask.\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction siga;
    memset(&siga, 0, sizeof(siga));
    siga.sa_handler = SIG_IGN;
    CHECK_NOT_EQ(sigaction(SIGPIPE, &siga, NULL), -1, "sigaction SIGPIPE");

    // ------------ SIGHANDLER THREAD ------------ //
    pthread_t sighandler_tid;

    int sigh_pipe[] = {-1, -1};
    CHECK_NOT_EQ( pipe(sigh_pipe), -1, "sighandler pipe");

    sigh_arg_t sigh_arg;
    sigh_arg.set = &mask;
    sigh_arg.pipe = sigh_pipe;

    if (pthread_create(&sighandler_tid, NULL, sighandler, &sigh_arg) != 0) {
        fprintf(stderr, "Couldn't create thread. Aborting\n");
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

    // ---------------- SELECT ---------------- //
    fd_set set, tmpset;

    FD_ZERO(&set);
    FD_ZERO(&tmpset);

    FD_SET(fd_sock, &set);
    FD_SET(sigh_pipe[R_ENDP], &set);

    int fd_max = (fd_sock > sigh_pipe[R_ENDP]) ? fd_sock : sigh_pipe[R_ENDP];

    while(!terminate){
        tmpset = set;

        CHECK_NOT_EQ( select(fd_max + 1, &tmpset, NULL, NULL, NULL), -1, "select");
        for(int i = 0; i <= fd_max; i++){
            if(!FD_ISSET(i, &tmpset)) continue;
            // i is set
            if(i == fd_sock){ // new connection request
                long fd_client;
                CHECK_NOT_EQ( fd_client = accept(fd_sock, (struct sockaddr*)NULL, NULL), -1, "accept");
                printf("Connected!\n");
                fflush(stdout);

                if(spawn_thread(fd_client) < 0)
                    exit(EXIT_FAILURE);
            }

            if(i == sigh_pipe[R_ENDP] && terminate){
                break;
            }
        }
    }

    if(fd_sock != -1) close(fd_sock);
    if(sigh_pipe[R_ENDP] != -1)
        close(sigh_pipe[R_ENDP]);

    int err;
    if( (err = pthread_join(sighandler_tid, NULL)) != 0){
        errno = err;
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
    return 0;
}
