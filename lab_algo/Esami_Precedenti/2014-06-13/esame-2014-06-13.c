#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct {
    string code;
    int credits;
    int difficulty;
} exam;

int cmp(const void* a, const void* b){
    exam* E = (exam*) a;
    exam* F = (exam*) b;

    if(E->credits == F->credits){
        if(E->difficulty == F->difficulty)
            return strcmp(E->code, F->code);
        else
            return E->difficulty - F->difficulty;
    }
    else 
        return F->credits - E->credits;
}

int main(){
    int N, K;
    exam* exam_list;

    scanf("%d", &K);
    scanf("%d", &N);

    exam_list = (exam*) malloc(N*sizeof(exam));

    for(int i = 0; i < N; i++){
        exam_list[i].code = (string) malloc(101*sizeof(char));
        scanf("%s", exam_list[i].code);
        scanf("%d", exam_list[i].credits);
        scanf("%d", exam_list[i].difficulty);
    }

    qsort(exam_list, N, sizeof(exam), cmp);

    // continue later

}