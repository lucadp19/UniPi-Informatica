#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* product(char* str, int k);

int main(){
    char* s1;
    char* s2;
    int k;

    s1 = (char*) malloc(1001*sizeof(char));
    scanf("%s", s1);
    scanf("%d", &k);
    
    s2 = product(s1, k);
    printf("%s\n", s2);

    free(s1);
    free(s2);

    return 0;
}

char* product(char* str, int k){
    int len = strlen(str);
    char* aux = (char*) malloc(k*(len + 1)*sizeof(char));
    
    for(int i = 0; i < k*len; i++){
        aux[i] = str[i%len];
    }
    aux[k*len] = '\0';

    return aux;
}