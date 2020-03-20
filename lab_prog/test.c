#include <stdio.h>

void func(int a);

void func(int a){
	printf("%d", a);
	int a = 10;
	printf("\n%d", a);
}

int main(void){
	int x = 15;
	func(x);
	return 0;
}
