#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>

#include "lib.h"

struct _node_t {
    int info;
    struct _node_t* next;
};
typedef struct _node_t node_t;

static node_t* buff = NULL;

static pthread_cond_t full  = PTHREAD_COND_INITIALIZER;
static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx  = PTHREAD_MUTEX_INITIALIZER;

static unsigned int seed;

void atomic_insert_into_buffer(int new_elem);
node_t* atomic_retrieve_from_buffer();
static void* producer(void* arg);
static void* consumer(void* arg);
int produce(unsigned int* seed);

int main(void){
    seed = time(NULL);

    pthread_t cons_id;
    pthread_t prod_id;

    int err;

    dbgprint("Printing before thread creation\n");

    
    if ( (err = pthread_create(&prod_id, NULL, &producer, NULL)) != 0){
        errno = err;
        perror("producer thread creation\n");
        exit(EXIT_FAILURE);
    }
    dbgprint("Printing inbetween thread creation\n");


    if ( (err = pthread_create(&cons_id, NULL, &consumer, NULL)) != 0){
        errno = err;
        perror("consumer thread creation");
        exit(EXIT_FAILURE);
    }
    dbgprint("Printing after thread creation\n");

    void* status_cons;
    void* status_prod;
    pthread_join(cons_id, &status_cons);
    pthread_join(prod_id, &status_prod);

    return 0;
}

void* producer(void* arg){
    int new_elem;
    dbgprint("Created producer!\n");

    while(true){
        new_elem = produce(&seed);
        atomic_insert_into_buffer(new_elem);
        printf("Producer: inserted %d.\n", new_elem);
        fflush(stdout);
        sleep(1);
    }

    return ((void*) 0);
}

static void* consumer(void* arg){
    node_t* ptx = NULL;
    dbgprint("Created consumer!\n");

    while(true){
        ptx = atomic_retrieve_from_buffer();
        printf("Consumer: retrieved %d.\n", ptx->info);
        fflush(stdout);
        sleep(1);
        free(ptx);
    }
    
    return ((void*) 0);
}

void atomic_insert_into_buffer(int new_elem){
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->info = new_elem;
    new_node->next = NULL;

    safe_pthread_mutex_lock(&mtx);
    while(buff != NULL) // buffer isn't empty => it's full
        safe_pthread_cond_wait(&full, &mtx);
    // now buff is empty
    buff = new_node;
    safe_pthread_cond_signal(&empty);
    safe_pthread_mutex_unlock(&mtx);
}

node_t* atomic_retrieve_from_buffer(){
    node_t* ptx = NULL;

    safe_pthread_mutex_lock(&mtx);
    while(buff == NULL) // buffer is empty
        safe_pthread_cond_wait(&empty, &mtx);
    // now buff isn'empty => it has only one element
    ptx = buff;
    buff = NULL;
    safe_pthread_cond_signal(&full);
    safe_pthread_mutex_unlock(&mtx);

    return ptx;
}

int produce(unsigned int *seed){
    int upper_bound = 1000;
    int lower_bound = 300;
    return (rand_r(seed) % (upper_bound - lower_bound));
}