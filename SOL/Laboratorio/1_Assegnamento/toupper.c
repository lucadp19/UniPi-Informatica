#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void strtoupper(const char* in, size_t len, char* out);

int main(int argc, char* argv[]){
    int len;

    if(argc != 2) {
        printf("2 arguments needed");
        return -1;
    }

    len = strlen(argv[1]);
    char* out = (char*)malloc(len * sizeof(char));
    strtoupper(argv[1], len, out);
    printf("The resulting string is: <%s>.\n", out);
    free(out);
    return 0;
}

void strtoupper(const char* in, size_t len, char* out){
    for(int i = 0; i < len; i++){
        if(in[i] == '\0'){
            out[i] = '\0';
            return;
        }

        out[i] = toupper(in[i]);
    }
}