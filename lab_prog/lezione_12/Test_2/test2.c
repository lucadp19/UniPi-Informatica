#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN 30

//Functions to be implemented:
void readbinary(char arr[], int *len, int *reps);
int sum1rec(char arr[], int len);
int existSubseq(char arr[], int len, int reps);

int char_to_int(char);
char int_to_char(int);

int main() {
    char arr[ARR_LEN];
    int len, reps, i;

    // Read and print the array;
    readbinary(arr, &len, &reps);
    printf("Array:\n");
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    //Computes how many 1's are occurring (RECURSIVE)
    printf("Totale occorrenze di 1: %d\n", sum1rec(arr, len));

    //Computes if a subsequence of exactly nreps 1's exists in the array
    if(existSubseq(arr, len, reps))
        printf("Condizione per %d uno contigui: VERA\n", reps);
    else
        printf("Condizione per %d uno contigui: FALSA\n", reps);
}

void readbinary(char arr[], int *len, int *reps) {
    int num;

    *len = 0;

    do {
        scanf("%d", &num);
        
        if(num == 0 || num == 1) {
            // if the number is 0 or 1 then it's put into the array
            // and the array's length is updated 
            arr[*len] = num;
            (*len)++;
        }
        // the last number is saved into *reps
        else *reps = num;

    } while(num == 0 || num == 1);
}

int sum1rec(char arr[], int len){
    if(len == 0)
        return 0;
    else {
        if(len == 1)
            return *arr;
        else
            return *arr + sum1rec(arr+1, len-1);
    }
}

int char_to_int(char a){
    /* 
    Function that returns 0 when the input 
    is the character '0', 1 when the input is the
    character '1'.
    */
    if(a == '0')
        return 0;
    if(a == '1')
        return 1;
}

int existSubseq(char arr[], int len, int reps) {
    int sub_len = 0;
    int found = 0;
    int i = 0;

    while(!found && i < len){
        if(arr[i] == 1) sub_len++;
        else sub_len = 0;

        if(sub_len == reps && (i == len-1 || arr[i+1] == 0))
            found = 1;
        else i++;
    }

    return found;
}