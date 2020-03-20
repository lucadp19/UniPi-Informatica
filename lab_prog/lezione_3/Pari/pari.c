#include <stdio.h>

int main(){
    int num;
    scanf("%d", &num);
    // num%2 restituisce 0 se num e' pari, 1 se e' dispari
    // dunque (1 - num%2) restituisce il valore cercato, in quanto
    // se num e' pari, (1 - num%2) = (1 - 0) = 1
    // se num e' dispari, (1 - num%2) = (1 - 1) = 0
    printf("%d\n", 1 - num%2);
    return 0;
}
