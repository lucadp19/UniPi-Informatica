#include <stdio.h>
#include <stdlib.h>

int DP(int length, int price[], int max_gain[], int sol[]){
    int max, max_l;

    if(max_gain[length] != -1) return max_gain[length];

    max = price[1] + DP(length-1, price, max_gain, sol);
    max_l = 1;

    for(int i = 2; i <= length; i++){
        int res = price[i] + DP(length-i, price, max_gain, sol);
        if(max < res){
            max = res;
            max_l = i;
        }
    }

    max_gain[length] = max;
    sol[length] = max_l;
    return max_gain[length];
}

int main(){
    int n;
    int *max_gain;
    int *price;
    int *sol;

    scanf("%d", &n);
    max_gain = (int*) malloc((n+1)*sizeof(int));
    price = (int*) malloc((n+1)*sizeof(int));
    sol = (int*) malloc((n+1)*sizeof(int));

    max_gain[0] = 0;
    for(int i = 1; i < n+1; i++){
        max_gain[i] = -1;
    }
    sol[0] = 0;
    for(int i = 1; i < n+1; i++){
        sol[i] = -1;
    }
    price[0] = 0;
    for(int i = 1; i < n+1; i++){
        scanf("%d", &price[i]);
    }

    printf("%d\n", DP(n, price, max_gain, sol));

    // printf("\nMAX GAIN: ");
    // for(int i = 0; i < n+1; i++)
    //     printf("%d ", max_gain[i]);
    // printf("\nSOLUTION: ");
    // for(int i = 0; i < n+1; i++)
    //     printf("%d ", max_gain[i]);
    // printf("\n\n");

    while(n > 0){
        printf("%d ", sol[n]);
        n = n - sol[n];
    }

    free(max_gain);
    free(sol);
    free(price);
    
    return 0;
}