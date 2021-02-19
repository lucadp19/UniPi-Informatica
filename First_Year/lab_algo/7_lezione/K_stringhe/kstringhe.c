#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct {
    string str;
    int freq;
} s_freq;

int ord_string(const void* str1, const void* str2){
    string* s1 = (string*) str1;
    string* s2 = (string*) str2;
    return strcmp(*s1, *s2);
}

int ord_s_freq_1(const void* a, const void* b){
    s_freq* p1 = (s_freq*) a;
    s_freq* p2 = (s_freq*) b;
    return (p2->freq) - (p1->freq);
}

int ord_s_freq_2(const void* a, const void* b){
    s_freq* p1 = (s_freq*) a;
    s_freq* p2 = (s_freq*) b;
    return strcmp(p1->str, p2->str);
}

int main(){
    int N, K;
    int j;
    string* v_string;
    s_freq* v_freq;

    scanf("%d %d", &N, &K);
    v_string = (string*) malloc(N*sizeof(string));
    v_freq = (s_freq*) malloc(N*sizeof(s_freq));
    for(int i = 0; i < N; i++){
        v_string[i] = (string) malloc(101*sizeof(char));
        scanf("%s", v_string[i]);
    }

    qsort(v_string, N, sizeof(string), ord_string);

    j = 0;
    v_freq[j].str = v_string[0];
    v_freq[j].freq = 1;

    for(int i = 1; i < N; i++){
        if(strcmp(v_string[i], v_string[i-1]) == 0){
            v_freq[j].freq++;
        } else {
            j++;
            v_freq[j].str = v_string[i];
            v_freq[j].freq = 1;
        }
    }

    qsort(v_freq, j+1, sizeof(s_freq), ord_s_freq_1);
    qsort(v_freq, K, sizeof(s_freq), ord_s_freq_2);

    for(int i = 0; i < K; i++){
        printf("%s\n", v_freq[i].str);
    }

    for(int i = 0; i < N; i++)
        free(v_string[i]);
    free(v_string);
    free(v_freq);

    return 0;
}