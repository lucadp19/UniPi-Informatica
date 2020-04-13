#include <stdio.h>
#include <stdlib.h>

int my_strlen(char* s);
char* my_strcat(char* s1, char* s2);

int main(){
    char* s1;
    char* s2;

    s1 = (char*) malloc(1001*sizeof(char));
    s2 = (char*) malloc(1001*sizeof(char));

    scanf("%s", s1);
    scanf("%s", s2);

    s1 = (char*) realloc(s1, my_strlen(s1)+my_strlen(s2)+1);
    s1 = my_strcat(s1, s2);

    printf("%s\n", s1);

    free(s1);
    free(s2);

    return 0;
}

int my_strlen(char* s){
    int len = 0;
    while(*s != '\0'){
        len++;
        s++;
    }
    return len;
}

char* my_strcat(char* s1, char* s2){
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    s1[len1+len2] = '\0';
    for(int i = 0; i < len2; i++)
        s1[i+len1] = s2[i];
    
    return s1;
}