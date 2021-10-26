#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <errno.h> 
#include <unistd.h>
#include <signal.h>

#include "lib.h"
#include "lists.h"
#include "hash.h"
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
#define HTABLE_LEN 128

typedef struct {
    int len;
    char* str;
} msg_t;

typedef struct {
    sigset_t* set;
    int* pipe;
} sigh_arg_t;

pthread_mutex_t fd_queue_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  fd_queue_empty = PTHREAD_COND_INITIALIZER;
list_t* fd_queue;

hashtable_t* fd_client_ht = NULL;
pthread_mutex_t ht_mtx = PTHREAD_MUTEX_INITIALIZER;

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
                // waking sleeping threads
                pthread_cond_broadcast(&fd_queue_empty);
                CHECK_NOT_EQ( close(pipe[W_ENDP]), -1, "close pipe");
                return NULL;
            
            default: ;
        }
    }
    return NULL;
}

void atomic_insert_into_buffer(int new_elem){
    safe_pthread_mutex_lock(&fd_queue_mtx);
    push_back(fd_queue, new_elem);
    safe_pthread_cond_signal(&fd_queue_empty);
    safe_pthread_mutex_unlock(&fd_queue_mtx);
}

int atomic_retrieve_from_buffer(){
    int info;

    safe_pthread_mutex_lock(&fd_queue_mtx);
    while(fd_queue->nelem == 0) // queue is empty
        safe_pthread_cond_wait(&fd_queue_empty, &fd_queue_mtx);
    info = pop_front(fd_queue);
    safe_pthread_mutex_unlock(&fd_queue_mtx);

    return info;
}

void* worker(void* arg){
    while(!terminate){
        printf("> Worker waiting for client!\n");
        fflush(stdout);
        int fd_client;

        safe_pthread_mutex_lock(&fd_queue_mtx);
        while(!terminate && fd_queue->nelem == 0) // queue empty
            safe_pthread_cond_wait(&fd_queue_empty, &fd_queue_mtx);
        
        // lock taken!
        if(!terminate) {
            fd_client = pop_front(fd_queue);
            safe_pthread_mutex_unlock(&fd_queue_mtx);
        } else{
            printf("> Worker terminated :(\n");
            fflush(stdout);
            safe_pthread_mutex_unlock(&fd_queue_mtx);
            break;
        }

        printf("> Worker got request!\n");
        fflush(stdout);

        int err = 0;

        do {
            // reading and fulfilling client request
            msg_t msg;
            int l;

            if( (l = readn(fd_client, &msg.len, sizeof(int))) == -1){
                perror("first read");
                err = -1;
                break;
            }
            if(l == 0) break; // client closed connection
            
            msg.str = calloc(msg.len, sizeof(char));
            if(msg.str == NULL){
                perror("calloc");
                err = -1;
                break;
            }

            if( (l = readn(fd_client, msg.str, msg.len * sizeof(char))) == -1){
                perror("second read");
                err = -1;
                free(msg.str);
                break;
            }

            to_upper(msg.str, msg.len);

            if( (l = writen(fd_client, &msg.len, sizeof(int))) == -1){
                perror("first write");
                err = -1;
                free(msg.str);
                break;
            }

            if( (l = writen(fd_client, msg.str, msg.len * sizeof(char))) == -1){
                perror("second write");
                err = -1;
                free(msg.str);
                break;
            }

            free(msg.str);            
        } while(1);
        // reached EOF => closing connection
        close(fd_client);
        safe_pthread_mutex_lock(&ht_mtx);
        hashtable_remove(fd_client_ht, fd_client);
        safe_pthread_mutex_unlock(&ht_mtx);

        if(err == 0)
            printf("> Worker completed connection! Connection with client <%d> closed!\n", fd_client);
        else printf("> Errors in connection. Connection with client <%d> closed.\n", fd_client);
        fflush(stdout);
    }
    return NULL;
}

void cleanup(){
    unlink(SOCKNAME);
}

int update_max(fd_set set, int fdmax) {
    for(int i = (fdmax-1); i>=0; --i)
	    if (FD_ISSET(i, &set)) 
            return i;
    return -1;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "There must be exactly one additional argument: the dimension of the thread pool.");
        exit(EXIT_FAILURE);
    }

    long N;
    if( (N = isNumber(argv[1])) < 0){
        fprintf(stderr, "The additional argument must be a positive integer.");
        exit(EXIT_FAILURE);
    }

    cleanup();
    atexit(cleanup);

    int err;

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
    
    // max file descriptor
    int fd_max = (fd_sock > sigh_pipe[R_ENDP]) ? fd_sock : sigh_pipe[R_ENDP];

    // ---------- INIT REQUEST QUEUE ---------- //
    CHECK_NOT_EQ(fd_queue = malloc(sizeof(list_t)), NULL, "malloc fd_queue");
    INITIALIZE_LIST(fd_queue);

    // ----------- INIT CLIENT HASHT ----------- //
    hashtable_t* fd_client_ht = NULL;
    CHECK_NOT_EQ( hashtable_init(&fd_client_ht, HTABLE_LEN), -1, "init hashtable");

    // ------------ WORKER THREADS ------------ //
    pthread_t* th_ids;
    CHECK_NOT_EQ( (th_ids = malloc(N * sizeof(pthread_t))), NULL, "malloc th_ids");

    for(int i = 0; i < N; i++){
        th_ids[i] = -1;
        if( (err = pthread_create(&(th_ids[i]), NULL, worker, (void*)NULL)) != 0){
            errno = err;
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // ---------------- SELECT ---------------- //
    fd_set set, tmpset;

    FD_ZERO(&set);
    FD_ZERO(&tmpset);

    FD_SET(fd_sock, &set);
    FD_SET(sigh_pipe[R_ENDP], &set);

    while(!terminate){
        tmpset = set;

        CHECK_NOT_EQ( select(fd_max + 1, &tmpset, NULL, NULL, NULL), -1, "select");
        for(int i = 0; i <= fd_max; i++){
            if(!FD_ISSET(i, &tmpset)) continue;
            // i is set

            if(i == fd_sock){ // new connection request
                long fd_client;
                CHECK_NOT_EQ( fd_client = accept(fd_sock, (struct sockaddr*)NULL, NULL), -1, "accept");
                printf("New connection with client <%ld>!\n", fd_client);
                fflush(stdout);

                atomic_insert_into_buffer(fd_client);

                // adding client to hashtable
                CHECK_NOT_EQ( hashtable_insert(fd_client_ht, fd_client), -1, "hashtable insert");
                continue;
            }
            
            if(i == sigh_pipe[R_ENDP] && terminate){ // signal received
                break;
            }
        }
    }

    if(fd_sock != -1) close(fd_sock);
    if(sigh_pipe[R_ENDP] != -1)
        close(sigh_pipe[R_ENDP]);

    // joining sighandler
    if( (err = pthread_join(sighandler_tid, NULL)) != 0){
        errno = err;
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    // joining workers
    for(int i = 0; i < N; i++){
        if( (err = pthread_join(th_ids[i], NULL)) != 0){
            errno = err;
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // closing all client connections
    hasht_iter_t* iter;
    CHECK_NOT_EQ( iter = malloc(sizeof(hasht_iter_t)), NULL, "malloc iter");
    hashtable_iter_init(iter);
    while(true){
        int err = hashtable_iter_get_next(fd_client_ht, iter);
        if(err == -2){ // end of ht
            break;
        }
        if(err == -1){ // error
            perror("hashtable get_next");
            return -1;
        }

        int fd_client = iter->info;
        close(fd_client);
        printf("Connection with <%d> closed.\n", fd_client);
    }
    free(iter);
    hashtable_free(fd_client_ht);

    free(th_ids);
    list_delete(fd_queue);

    return 0;
}
