#include <stdio.h>

float media(int[], int);

int main(){
    int n = 10;
    int i;
    int array[10];
    for (i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("%f\n", media(array, n));
    return 0;
}

float media(int array[], int n){
    float sum = 0;
    int i;
    int c = 0;
    for (i = 0; i < n; i++){
        if (array[i] * array[n-1] > 0){
            sum += array[i];
            c++;
        }
    }
    return sum/c;
}
