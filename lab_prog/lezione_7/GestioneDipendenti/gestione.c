#include <stdio.h>

typedef struct {
    int id;
    int stipendio;
    int mese;
    int anno;
} dipendente;

void aumenta(dipendente v[], int dim, int perc) {
    int i;
    for (i = 0; i < dim; i++)
        if(v[i].anno < 2000 || (v[i].anno == 2000 && v[i].mese < 5))
            v[i].stipendio += v[i].stipendio * (float)perc / 100;
}

int main() {
    const int dim = 2;
    dipendente dip[dim];
    int i, perc;

    for (i = 0; i < dim; i++)
        scanf("%d %d %d %d", &dip[i].id, &dip[i].mese, &dip[i].anno, &dip[i].stipendio);
    scanf("%d", &perc);

    aumenta(dip, dim, perc);

    for (i = 0; i < dim; i++)
        if(dip[i].stipendio > 1200)
            printf("%d %d\n", dip[i].id, dip[i].stipendio);
    
    return 0;
}