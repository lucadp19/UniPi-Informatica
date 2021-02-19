#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct {
    string original;
    string anagram;
} pair;

int orderPairs(const void* s1, const void* s2){
    int cmp_value = strcmp(((pair *) s1)->anagram, ((pair *) s2)->anagram);
    if(cmp_value == 0)
        return strcmp(((pair *) s1)->original, ((pair *) s2)->original);
    else return cmp_value;
}

int orderString(const void* c1, const void* c2){
    return *((char*) c1) - *((char*) c2);
}

int main(){
    int N;
    pair* str_pair;
    scanf("%d", &N);
    str_pair = (pair*) malloc(N*sizeof(pair));

    for(int i = 0; i < N; i++){
        str_pair[i].original = (string) malloc(21*sizeof(char));
        str_pair[i].anagram = (string) malloc(21*sizeof(char));
        scanf("%s", str_pair[i].original);

        strcpy(str_pair[i].anagram, str_pair[i].original);
        qsort(str_pair[i].anagram, strlen(str_pair[i].anagram), sizeof(char), orderString);
    }

    qsort(str_pair, N, sizeof(pair), orderPairs);

    for(int i = 0; i < N; i++){
        if(i != 0 && strcmp(str_pair[i].anagram, str_pair[i-1].anagram) != 0)
            printf("\n");
        printf("%s ", str_pair[i].original);
    }

    for(int i = 0; i < N; i++){
        free(str_pair[i].original);
        free(str_pair[i].anagram);
    }
    free(str_pair);
}