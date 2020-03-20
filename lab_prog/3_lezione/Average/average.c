#include <stdio.h>

int main(){
    float num1, num2, num3, avg; // rispettivamente i 3 numeri da leggere in input, e la media
    scanf("%f %f %f", &num1, &num2, &num3);
    avg = (num1 + num2 + num3)/3;
    printf("%0.3f\n", avg);
    return 0;
}
