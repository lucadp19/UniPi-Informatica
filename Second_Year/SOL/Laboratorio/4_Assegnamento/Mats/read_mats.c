#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/utils.h"

#define ELEM(M, i, j, N) M[i + j*N]

int compare(int (*cmp)(const void*, const void*, size_t), void* first, void* second, size_t dim);

int main(int argc, char* argv[]){
    if(argc != 4){
        fprintf(stderr, "There must be exactly three additional argument.");
        return -1;
    }

    int N;

    if ((N = isNumber(argv[3])) < 0){
        fprintf(stderr, "The last argument must be a positive integer, smaller than 512.");
        return -1;
    } else if (N > 512){
        fprintf(stderr, "The last argument must be less or equal than 512.");
        return -1;
    }

    float* m1 = malloc(N * N * sizeof(float));
    float* m2 = malloc(N * N * sizeof(float));

    FILE *bin_in, *txt_in;
    FOPEN_ERR (bin_in, argv[1], "rb");
    FOPEN_ERR (txt_in, argv[2], "r");

    fread(m1, sizeof(float), N*N, bin_in);
    for(int i = 0; i < N*N; i++)
        fscanf(txt_in, "%f", &m2[i]);
    
    printf("The result is: %d.\n", compare(memcmp, m1, m2, N*N*sizeof(float)));

    free(m1);
    free(m2);
    
    fclose(bin_in);
    fclose(txt_in);
    return 0;
}

int compare(int (*cmp)(const void*, const void*, size_t), void* first, void* second, size_t dim){
    return cmp(first, second, dim);
}