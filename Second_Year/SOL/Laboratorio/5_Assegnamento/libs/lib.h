#ifndef _LIB_H
#define _LIB_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>

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

#define CHECK_NOTEQ(expr, val, errstr) \
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

#endif