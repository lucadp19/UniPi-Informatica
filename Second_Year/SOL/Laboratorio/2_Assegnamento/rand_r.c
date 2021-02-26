#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Default values for N, K1, K2
#define STD_N 1000
#define STD_K1 100
#define STD_K2 120

long isNumber(const char* s); 

int main(int argc, char* argv[]){
    if(argc != 1 && argc != 4){
        fprintf(stderr, "There must be either 0 additional arguments or 3.\n");
        return -1;
    }

    int N, K1, K2;
    if(argc == 1){
        N = STD_N;
        K1 = STD_K1;
        K2 = STD_K2;
    } else {
        N = isNumber(argv[1]);
        K1 = isNumber(argv[2]);
        K2 = isNumber(argv[3]);

        if(N <= 0 || K1 <= 0 || K2 <= 0){
            fprintf(stderr, "All arguments must be numeric and greater than 0.\n");
            return -1;
        }
    }

    // array containing the occurrences
    int* occ = calloc(K2 - K1, sizeof(int));
    // seed
    unsigned int seed = time(NULL);

    for(int i = 0; i < N; i++){
        // generating numbers in [0, K2-K1)
        // when printing K1 is added to every number, 
        //  so that the random numbers will be in [K1, k2)
        occ[rand_r(&seed) % (K2 - K1)]++;
    }
    printf("Occorrenze di:\n");
    for(int i = 0; i < K2 - K1; i++)
        printf("%-8d:%8.2f%%\n", i+K1, (100.0*occ[i])/N);
    
    free(occ);
    return 0;
}

long isNumber(const char* s) {
    char* e = NULL;
    long val = strtol(s, &e, 0);
    if (e != NULL && *e == (char)0) 
        return val; 
    return -1;
}