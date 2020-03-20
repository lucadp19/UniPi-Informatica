#include <stdio.h>

int main(){
    int sec, hours, min; // rispettivamente secondi, ore e minuti
    scanf("%d", &sec);
    hours = sec/3600; // in un ora ci sono 3600 secondi
    sec %= 3600; // il resto della divisione rappresentano i minuti e i secondi rimanenti
    min = sec/60; // in un minuto ci sono 60 secondi
    sec %= 60;
    printf("%d h %d min %d s\n", hours, min, sec);
    return 0;
}
