#include <stdio.h>
#include <math.h>

int is_prime(int n);

int main(){
    int n;
    scanf("%d", &n);
    printf("%d\n", is_prime(n));

    return 0;
}

int is_prime(int n){
    int root = (int)sqrt(n) + 1;
    for(int i = 2; i < root; i++)
        if(n%i==0)
            return 0;
    return 1;
}