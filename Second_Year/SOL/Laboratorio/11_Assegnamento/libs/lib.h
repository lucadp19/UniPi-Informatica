#ifndef _LIB_H
#define _LIB_H

#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <pthread.h>

#include <stdarg.h>

#include <stdlib.h>
#include <stdio.h>

// Debug macro
#ifdef DEBUG
#define dbgprint(...) \
    _debug_printf(__FILE__, __LINE__, __VA_ARGS__)

int _debug_printf(const char* file, const int line, const char* fmt, ...){
    va_list argp;
    va_start (argp, fmt);

    fprintf(stderr, ">>> DBG: [%s : %d]\n", file, line);
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "<<<\n");

    va_end(argp);
    return 0;
}

#else
#define dbgprint(...)

#endif

#define MODE_TO_STRING(str, mode) \
    switch(mode) { \
        case O_RDONLY: \
            str = "read-only"; \
            break; \
        case O_WRONLY: \
            str = "write-only"; \
            break; \
        case O_RDWR: \ \
            str = "read and write"; \
            break; \
        default: \
            str = "complex mode"; \
            break; \
    }

#define SAFE_OPEN(fd, filename, flag) \
    if ((fd = open(filename, flag)) == -1){ \
        perror(filename); \
        exit(EXIT_FAILURE); \
    } \

#define SAFE_CLOSE(fd) \
    if(close(fd) == -1) { \
        perror("File closure error"); \
        exit(EXIT_FAILURE); \
    }

#define SAFE_FOPEN(file, filename, mode) \
    if((file = fopen(filename, mode)) == NULL){ \
        perror("fopen error"); \
        exit(EXIT_FAILURE); \
    }

#define SAFE_FCLOSE(file) \
    if(fclose(file) == EOF){ \
        perror("fclose error"); \
        exit(EXIT_FAILURE); \
    }

#define CHECK_NOT_EQ(expr, val, errstr) \
    if((expr) == (val)){ \
        perror(#errstr); \
        exit(EXIT_FAILURE); \
    }

#define CHECK_EQ(expr, val, errstr) \
    if((expr) != (val)){ \
        perror(#errstr); \
        exit(EXIT_FAILURE); \
    }

#define ERROR_EXIT(errstr) \
    do { \
        fprintf(stderr, #errstr); \
        exit(EXIT_FAILURE); \
    } while (0);

long isNumber(const char* s);
void* safe_malloc(size_t size); 


void safe_pthread_mutex_lock(pthread_mutex_t* mtx);
void safe_pthread_mutex_unlock(pthread_mutex_t* mtx);
void safe_pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mtx);
void safe_pthread_cond_signal(pthread_cond_t* cond);


#endif