#include <stdio.h>

int min_azzera(int[], int);

int main(){
    int i, min;
    int v[10];
    const int n = 10;
    for(i = 0; i < n; i++)
        scanf("%d", &v[i]);
    min = min_azzera(v, n);
    for(i = 0; i < n; i++)
        printf("%d\n", v[i]);
    printf("%d\n", min);
    return 0;
}

int min_azzera(int v[], int n){
    int i;
    int min = v[0];
    for(i = 1; i < n; i++){
        if(*(v+i) < min) 
            min = *(v+i);
        if(i%2)
            *(v+i) = 0;
    }
    return min;
}
