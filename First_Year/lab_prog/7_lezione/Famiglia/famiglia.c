#include <stdio.h>

struct persona {
    char nome[10];
    struct persona *mamma;
    struct persona *babbo;
};
typedef struct persona Persona;

void stampaPersone(Persona);
void stampaStringa(char[], int);

int main() {
    Persona p1, p2, p3;

    for(int i = 0; i < 30; i++){
        if (i < 10)
            scanf("%c", &p1.nome[i%10]);
        else if (i >= 10 && i < 20)
            scanf("%c", &p2.nome[i%10]);
        else
            scanf("%c", &p3.nome[i%10]);
    }

    p1.mamma = &p2;
    p1.babbo = &p3;
    p2.mamma = NULL;
    p2.babbo = NULL;
    p3.mamma = NULL;
    p3.babbo = NULL;

    stampaPersone(p1);
    stampaPersone(p2);
    stampaPersone(p3);

    return 0;
}

void stampaStringa(char str[], int len){
    int i;
    for(i = 0; i < len; i++)
        printf("%c", str[i]);
}

void stampaPersone(Persona p){
    stampaStringa(p.nome, 10);
    printf("\n");

    if(p.mamma != NULL)
        stampaStringa(p.mamma -> nome, 10);
    else
        printf("Sconosciuto");
    
    if(p.babbo != NULL)
        stampaStringa(p.babbo -> nome, 10);
    else
        printf("Sconosciuto");

    printf("\n");
}
