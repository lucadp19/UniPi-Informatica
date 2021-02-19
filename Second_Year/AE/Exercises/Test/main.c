#include <stdio.h>
#include <string.h>
extern int match(char *, char *, int);
extern int mystrstr(char *, char *);
// extern void mystrs(char *, char *);

int main(int argc, char ** argv) {
    char * stringa = "cercare in questa stringa";
    char * p1 = "questa";
    char * p2 = "cercare";
    char * p3 = "stringa";

    int t1 = mystrstr(stringa, p1);
    int t2 = mystrstr(stringa, p2);
    int t3 = mystrstr(stringa, p3);
    if(t1 == 11 && t2 == 0 && t3 == 18)
        printf("Corretto\n");
    else
        printf("Sbagliato\n");
    return 0;
}