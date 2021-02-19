#include <stdio.h>

void tswap(int* x, int* y, int* z){
    int xcopy = *x;
    int ycopy = *y;

    *x = *z;
    *y = xcopy;
    *z = ycopy;
}

int main(){
    int a[3];
    scanf("%d %d %d", &a[0], &a[1], &a[2]);
    tswap(a, a+1, a+2);
    printf("%d\n%d\n%d\n", a[0], a[1], a[2]);
    return 0;
}