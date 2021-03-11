#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/utils.h"

#define MAX_LEN 100
#define PASSWD "/etc/passwd"

int main(int argc, char* argv[]){
    if(argc == 1)
        printf("Printing result on stdout:\n");
    else if(argc > 2) {
        fprintf(stderr, "There must be at most one additional argument to program %s.", argv[0]);
        return -1;
    }

    FILE* passwin;
    FILE* passwout;
    char* str;

    FOPEN_ERR(passwin, PASSWD, "r");
    if(argc == 1) passwout = stdout;
    else FOPEN_ERR(passwout, argv[1], "w");

    str = malloc(MAX_LEN * sizeof(char));

    while(fgets(str, MAX_LEN, passwin) != NULL){
        char* first_occ = strchr(str, ':');
        *first_occ = '\0';
        fprintf(passwout, "%s\n", str);
    }

    fclose(passwin);
    if(argc == 2) fclose(passwout);
    free(str);

    return 0;
}
