#include <stdio.h>

int main(){
    int i;
    int n = 5;
    int vet1[5];
    int vet2[5];

    for(i = 0; i < n; i++)
        scanf("%d", &vet1[i]);
    for(i = 0; i < n; i++)
        scanf("%d", &vet2[i]);

    printf("[");
    for (i = 0; i < n; i++){
        printf("%d", vet1[i]);
        if(i != n-1)
            printf(",");
    }
    printf("]\n[");
    for (i = 0; i < n; i++){
        printf("%d", vet2[i]);
        if(i != n-1)
            printf(",");
    }
    printf("]\n[");
    for (i = 0; i < n; i++){
        printf("%d", vet1[i] + vet2[i]);
        if(i != n-1)
            printf(",");
    }
    printf("]\n");
    
    return 0;
}   
