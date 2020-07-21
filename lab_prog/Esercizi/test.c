#include <stdio.h>

int main(){
    int n;
    int s = 0;
    scanf("%d", &n);
    while(n != 0){
        s++;
        scanf("%d", &n);
    }
    printf("%d", s);
}