#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
const int REALLOC_INC=16;
 
void RIALLOCA(char** buf, size_t newsize) {
    *buf = (char*)realloc(*buf, newsize);
    if(*buf == NULL){
        printf("bahh");
    }
}

char* mystrcat(char *buf, size_t sz, char *first, ...) {
    va_list ap;
    va_start (ap, first);
    
    // length of the current list
    int curr_len = strlen(first);
    // length of the occupied portion of the buffer
    int occ = 0;
    
    if(curr_len + 1 > sz){
        sz += curr_len + 1;
        RIALLOCA(&buf, sz);
    }
    strncpy(buf, first, curr_len);
    occ += curr_len;

    char* next = va_arg(ap, char*);
    while(next != NULL){
        curr_len = strlen(next);

        if(curr_len + 1 > sz - occ){
            sz += curr_len + 1;
            RIALLOCA(&buf, sz);
        }

        strncat(buf, next, curr_len);
        occ += curr_len;
        next = va_arg(ap, char*);
    }
    // buf[occ] = '\0';

    va_end (ap);
    return buf;
}  
 
int main(int argc, char *argv[]) {
    if (argc != 7) { 
        printf("troppi pochi argomenti\n"); 
        return -1; 
    }
    char *buffer=NULL;

    RIALLOCA(&buffer, REALLOC_INC);  // macro che effettua l'allocazione del 'buffer'
    buffer[0]='\0'; // mi assicuro che il buffer contenga una stringa

    buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);

    printf("%s\n", buffer);     
    free(buffer);
    return 0;
}