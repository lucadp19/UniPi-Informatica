#include <stdio.h>

int MCD(int, int);
int mcm(int, int);

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    printf("%d\n%d\n", MCD(n, m), mcm(n, m));
}

int MCD(int a, int b){
    int temp;
    while(b != 0){
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int mcm(int a, int b){
    return (a*b)/MCD(a, b);
}
