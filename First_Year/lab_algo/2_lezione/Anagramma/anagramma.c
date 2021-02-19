#include <stdio.h>

int anagramma(unsigned char* s1, unsigned char* s2);
void reset(int freq[], int len);
void add(int freq[], int len, int val);
void check_if_same(int freq1[], int freq[2], int len);

int main(){
    unsigned char s1[100], s2[100];
    scanf("%s", s1);
    scanf("%s", s2);
    printf("%d\n", anagramma(s1, s2));
    return 0;    
}

int anagramma(unsigned char* s1, unsigned char* s2){
    const int len = 256;
    int freq1[len], freq2[len];
    int i = 0;

    reset(freq1, len);
    reset(freq2, len);
    
    while(s1[i] != '\0')
        add(freq1, len, s1[i++]);

    i = 0;
    while(s2[i] != '\0')
        add(freq2, len, s2[i++]);

    for(i = 0; i < len; i++)
        if(freq1[i] != freq2[i])
            return 0;
    return 1;
}

void reset(int freq[], int len){
    for(int i = 0; i < len; i++)
        freq[i] = 0;
}

void add(int freq[], int len, int val){
    if(val >= 0 && val < len)
        freq[val]++;
}