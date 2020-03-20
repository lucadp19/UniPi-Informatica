#include <stdio.h>

void ordered_swap(int*, int*, int*);

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	ordered_swap(&a, &b, &c);
	printf("%d\n%d\n%d\n", a, b, c);
	return 0;
}

void ordered_swap(int* a, int* b, int *c){
	int temp;
	if (*a > *b){
		temp = *a;
		*a = *b;
		*b = temp;
	} 
    if (*b > *c) {
		temp = *b;
		*b = *c;
		*c = temp;
	} 
    if (*a > *b) {
		temp = *a;
		*a = *b;
		*b = temp;
	}
}
