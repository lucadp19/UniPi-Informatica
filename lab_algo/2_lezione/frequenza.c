#include <stdio.h>

void reset(int freq[], int len);
void add(int freq[], int len, int val);

int main(){
    int freq[10];
    int num;

    reset(freq, len);

    do {
        scanf("%d", &num);
        add(freq, 10, num);
    } while(num >= 0);

    for(int i = 0; i < 10; i++)
        printf("%d\n", freq[i]);
}

void reset(int freq[], int len){
    for(int i = 0; i < len; i++)
        freq[i] = 0;
}

void add(int freq[], int len, int val){
    if(val >= 0 && val < len)
        freq[val]++;
}