#include <stdio.h>

float sum_pow(float, int);

int main(){
    int n;
    float x;

    scanf("%d %f", &n, &x);

    printf("%.2f\n", sum_pow(x, n));
    return 0;
}

float sum_pow(float x, int n){
    float curr_pow = 1; // la potenza iniziale e' x^0 = 1
    float sum = curr_pow; // la somma delle potenze all'inizio e' uguale a x^0 = 1
    int i;

    for(i = 1; i <= n; i++){
        curr_pow *= x;
        sum += curr_pow; 
    }
    
    return sum;
}
