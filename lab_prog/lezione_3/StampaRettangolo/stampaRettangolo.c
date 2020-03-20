#include <stdio.h>

int main(){
    int i;
    for (i = 0; i < 10; i++){
        if (i == 0 || i == 9)
            printf("***\n");
        else
            printf("*X*\n");
    }
    return 0;
}
