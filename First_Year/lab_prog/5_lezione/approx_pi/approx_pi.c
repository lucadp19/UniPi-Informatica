#include <stdio.h>

float approx_pi(int);

int main(){
    int n;
    scanf("%d", &n);
    printf("%.6f\n", approx_pi(n));
    return 0;
}

float approx_pi(int reps){
    int i;
    int sign = 1;
    float pi = 0;

    for(i = 0; i < reps; i++){
        pi += sign * 4.0 / (2*i + 1);
        sign *= -1;
    }

    return pi;
}
