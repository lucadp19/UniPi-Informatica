#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#include <sys/types.h>
#include <sys/wait.h>

// #define DEBUG

#include "lib.h"
#include "lists.h"

list_t* buff = NULL;

typedef struct {
    int num_prod;
    int thread_n;
} thread_arg_t;

static unsigned int seed;
static bool end_of_production = false;

static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx  = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t empty_eop = PTHREAD_COND_INITIALIZER;

void* producer(void* arg);
void* consumer(void* arg);
void atomic_insert_into_buffer(int new_elem);
int atomic_retrieve_from_buffer();
int produce(unsigned int* seed);

int main(int argc, char* argv[]){
    seed = time(NULL);

    if(argc != 4){
        fprintf(stderr, "There must be three additional arguments. Aborting.");
        exit(EXIT_FAILURE);
    }

    int N, M, K;
    if( (N = isNumber(argv[1])) < 0 ||
        (M = isNumber(argv[2])) < 0 ||
        (K = isNumber(argv[3])) < 0) {
        fprintf(stderr, "The three additional arguments must be positive integers. Aborting.");
        exit(EXIT_FAILURE);
    }

    buff = (list_t*)malloc(sizeof(list_t));
    INITIALIZE_LIST(buff);

    dbgprint("Printing before thread creation\n");
    pthread_t* prod_ids = calloc(N, sizeof(pthread_t));
    pthread_t* cons_ids = calloc(M, sizeof(pthread_t));

    thread_arg_t** prod_args = (thread_arg_t**)safe_malloc(N * sizeof(thread_arg_t*));
    int* cons_args = (int*)safe_malloc(M * sizeof(int));

    for(int i = 0; i < N; i++){
        prod_args[i] = (thread_arg_t*)safe_malloc(sizeof(thread_arg_t));
        prod_args[i]->num_prod = K/N;
        prod_args[i]->thread_n = i;
    }

    for(int i = 0; i < M; i++){
        cons_args[i] = i;
    }

    dbgprint("N = %d\nM = %d\nK = %d\n", N, M, K);

    for(int i = 0; i < N; i++){
        dbgprint("Creating thread %d\n", i);
        int err;
        if ( (err = pthread_create(&prod_ids[i], NULL, &producer, prod_args[i])) != 0){
            errno = err;
            perror("producer thread creation\n");
            exit(EXIT_FAILURE);
        }
    }

    #ifdef DEBUG
    dbgprint("Printing inbetween thread creation\n");
    for (int i = 0; i < N; i++) {
        dbgprint("Consumer %d: %d", i, cons_ids[i]);
        dbgprint("Producer %d: %d", i, prod_ids[i]);
    }
    #endif

    for(int i = 0; i < M; i++) {
        int err;
        if ( (err = pthread_create(&cons_ids[i], NULL, &consumer, &cons_args[i])) != 0){
            errno = err;
            perror("consumer thread creation");
            exit(EXIT_FAILURE);
        }
    }

    dbgprint("Printing after thread creation\n");

    for(int i = 0; i < N; i++){
        dbgprint("Joining thread %d with id %d", i, prod_ids[i]);
        int err;
        if ((err = pthread_join(prod_ids[i], NULL)) == -1){
            errno = err;
            perror("join error");
            exit(EXIT_FAILURE);
        }
    }

    // waiting for the queue to be empty ???
    safe_pthread_mutex_lock(&mtx);
    end_of_production = true;
    while(buff->nelem != 0)
        safe_pthread_cond_wait(&empty_eop, &mtx);
    safe_pthread_mutex_unlock(&mtx);

    // sending termination signal to consumers
    for(int i = 0; i < M; i++)
        atomic_insert_into_buffer(-1);
    
    for(int i = 0; i < M; i++){
        void* status;
        pthread_join(cons_ids[i], &status);
    }

    for(int i = 0; i < N; i++)
        free(prod_args[i]);
    
    free(prod_args);
    free(cons_args);
    
    free(cons_ids);
    free(prod_ids);

    return 0;
}

void* producer(void* arg){
    int new_elem;
    thread_arg_t* thread_arg = (thread_arg_t*) arg;

    dbgprint("Created producer %d!\n", thread_arg->thread_n);
    
    for(int i = 0; i < thread_arg->num_prod; i++){
        new_elem = produce(&seed);
        atomic_insert_into_buffer(new_elem);
        printf("Producer %d: inserted %d.\n", thread_arg->thread_n, new_elem);
        fflush(stdout);
        // sleep(1);
    }
    return ((void*) 0);
}

void* consumer(void* arg){
    int info;
    const int thread_num = *(int*)arg;
    dbgprint("Created consumer %d!\n", thread_num);

    while(true){
        info = atomic_retrieve_from_buffer();
        if(info > 0){
            printf("Consumer %d: retrieved %d.\n", thread_num, info);
            fflush(stdout);
            // sleep(1);
        } else {
            printf("Consumer %d: recieved shutdown signal.\n", thread_num);
            fflush(stdout);
            break;
        }
    }
    return ((void*) 0);
}

void atomic_insert_into_buffer(int new_elem){
    safe_pthread_mutex_lock(&mtx);
    push(buff, new_elem);
    safe_pthread_cond_signal(&empty);
    safe_pthread_mutex_unlock(&mtx);
}

int atomic_retrieve_from_buffer(){
    int info;
    safe_pthread_mutex_lock(&mtx);
    while(buff->nelem == 0) {// buffer is empty
        if(end_of_production == true)
            safe_pthread_cond_signal(&empty_eop);
        safe_pthread_cond_wait(&empty, &mtx);
    }
    info = pop(buff);
    safe_pthread_mutex_unlock(&mtx);

    return info;
}

int produce(unsigned int *seed){
    int upper_bound = 1000;
    int lower_bound = 300;
    return (rand_r(seed) % (upper_bound - lower_bound));
}