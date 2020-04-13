#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strcmp(char* s1, char* s2);

int main(){
    char* s1;
    char* s2;
    int cmp;

    s1 = (char*) malloc(1001*sizeof(char));
    s2 = (char*) malloc(1001*sizeof(char));

    scanf("%s", s1);
    scanf("%s", s2);

    cmp = my_strcmp(s1, s2);
    if(cmp == 1) printf("+");
    printf("%d\n", cmp);

    free(s1);
    free(s2);

    return 0;
}
int my_strcmp(char* s1, char* s2){
    int cmp = 0;

    while(*s1 != '\0' && *s2 != '\0' && cmp == 0){
        // printf("%c %c\n", *s1, *s2);
        if(*s1 == *s2){
            s1++;
            s2++;
        } else if(*s1 < *s2){
            cmp = -1;
        } else {
            cmp = 1;
        }      
    }

    // if(*s1 == '\0') printf("\nNULL ");
    // else printf("\n%c ", *s1);
    // if(*s2 == '\0') printf("NULL ");
    // else printf("%c ", *s2);
    // printf("%d\n", cmp);

    if(cmp != 0)
        return cmp;
    
    if(*s1 != '\0' && *s2 == '\0')
        return 1;
    else if(*s1 == '\0' && *s2 != '\0')
        return -1;
    else return 0;
}