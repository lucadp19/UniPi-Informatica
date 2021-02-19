#include <stdio.h>

int count_larger(int, int[], int);

int main(){
    int array[5];
    int n = 5;
    int x, i;

    scanf("%d", &x);
    for(i = 0; i < n; i++)
        scanf("%d", &array[i]);

    printf("%d\n", count_larger(x, array, n));
}

int count_larger(int x, int array[], int n){
    int i;
    int count = 0;
    for(i = 0; i < n; i++)
        if(array[i] > x)
            count++;
    return count;
}
