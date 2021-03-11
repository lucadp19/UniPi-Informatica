#ifndef _UTILS_H

#define _UTILS_H

#define FOPEN_ERR(file, path, mode) do { \
        if ((file = fopen(path, mode)) == NULL){ \
            fprintf(stderr, "Could not open file %s in mode <%s>. Aborting.", path, mode); \
            exit(-1); \
        } \
    } while(0) 

long isNumber(const char* s); 

#endif