#include <stdio.h>

int my_strlen(char* s);

int main(){
    char s[1000];

    scanf("%s", s);
    printf("%d", my_strlen(s));

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