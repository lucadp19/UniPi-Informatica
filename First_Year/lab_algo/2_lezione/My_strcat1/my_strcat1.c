#include <stdio.h>
#include <stdlib.h>

int my_strlen(char* s);
char* my_strcat(char* s1, char* s2);

int main(){
    char s1[1000], s2[1000];
    char* s;

    scanf("%s", s1);
    scanf("%s", s2);
    s = my_strcat(s1, s2);
    printf("%s", s);

    free(s);

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
    int len = len1 + len2 + 1;
    char* s = malloc(len*sizeof(char));

    s[len-1] = '\0';
    for(int i = 0; i < len - 1; i++){
        if(i < len1)
            s[i] = s1[i];
        else
            s[i] = s2[i-len1];
    }

    return s;
}