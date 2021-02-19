#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strcpy(char* dest, char* src);

int main(){
    char* s1;
    char* s2;

    s1 = (char*) malloc(1001*sizeof(char));
    scanf("%s", s1);
    
    s2 = (char*) malloc((strlen(s1) + 1)*sizeof(char));
    s2 = strcpy(s2, s1);
    printf("%s\n", s2);

    free(s1);
    free(s2);
    
    return 0;
}

char* my_strcpy(char* dest, char* src){
    char* aux = dest;
    while(*src != '\0'){
        *aux = *src;
        aux++;
        src++; 
    }
    *aux = '\0';

    return dest;
}