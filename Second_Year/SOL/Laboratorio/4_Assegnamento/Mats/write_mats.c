#include <stdio.h>
#include <stdlib.h>
#include "../Utils/utils.h"

#define ELEM(M, i, j, N) M[i + j*N] 
#define INITIALIZE_MAT(M, N)       \
    for(int i = 0; i < N; i++)      \
        for(int j = 0; j < N; j++)      \
            ELEM(M, i, j, N) = (i+j)/2.0;

#define BIN_DUMP "./mat_dump.dat"
#define TXT_DUMP "./mat_dump.txt"

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "There must be exactly one additional argument.");
        return -1;
    }

    int N;

    if ((N = isNumber(argv[1])) < 0){
        fprintf(stderr, "The additional argument must be a positive integer, smaller than 512.");
        return -1;
    } else if (N > 512){
        fprintf(stderr, "The additional argument must be less or equal than 512.");
        return -1;
    }

    float* matrix = malloc(N * N * sizeof(float));
    INITIALIZE_MAT(matrix, N);

    FILE *bin_out, *txt_out;
    FOPEN_ERR (bin_out, BIN_DUMP, "wb");
    FOPEN_ERR (txt_out, TXT_DUMP, "w");

    fwrite(matrix, sizeof(float), N*N, bin_out);
    for(int i = 0; i < N*N; i++)
        fprintf(txt_out, "%f\n", matrix[i]);
    
    printf("Files written. :)\n");
    free(matrix);
    fclose(bin_out);
    fclose(txt_out);
    return 0;
}

// long isNumber(const char* s) {
//     char* e = NULL;
//     long val = strtol(s, &e, 0);
//     if (e != NULL && *e == (char)0) 
//         return val; 
//     return -2;
// }