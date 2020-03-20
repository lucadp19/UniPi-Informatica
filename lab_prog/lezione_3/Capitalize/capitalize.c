#include <stdio.h>

int main(){
    char c;
    scanf("%c", &c);
    // le lettere minuscole sono 32 posti dopo le maiuscole nella tabella ASCII
    // dunque sottraendo 32 al carattere considerato otteniamo la versione maiuscola
    printf("%c\n", c-32);
    return 0;
}
