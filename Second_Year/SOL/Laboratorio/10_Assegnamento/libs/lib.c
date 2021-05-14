#include "lib.h"

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -2;
}

void* safe_malloc(size_t size){
    void* ptr;
    if((ptr = malloc(size)) == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void safe_pthread_mutex_lock(pthread_mutex_t *mtx){
    int err;
    if( (err = pthread_mutex_lock(mtx)) != 0) {
        errno = err;
        perror("lock");
        pthread_exit((void*) errno); // can be changed
    } else {
        dbgprint("locked\n"); // can be commented when the program is finished
    }
}

void safe_pthread_mutex_unlock(pthread_mutex_t *mtx){
    int err;
    if( (err = pthread_mutex_unlock(mtx)) != 0) {
        errno = err;
        perror("unlock");
        pthread_exit((void*) errno); // can be changed
    } else {
        dbgprint("unlocked\n"); // can be commented when the program is finished
    }
}

void safe_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mtx){
    int err;
    if( (err = pthread_cond_wait(cond, mtx)) != 0) {
        errno = err;
        perror("cond_wait");
        pthread_exit((void*) errno); // can be changed
    } else {
        dbgprint("waiting\n"); // can be commented when the program is finished
    }
}

void safe_pthread_cond_signal(pthread_cond_t *cond){
    int err;
    if( (err = pthread_cond_signal(cond)) != 0) {
        errno = err;
        perror("cond_signal");
        pthread_exit((void*) errno); // can be changed
    } else {
        dbgprint("signaled\n"); // can be commented when the program is finished
    }
}
