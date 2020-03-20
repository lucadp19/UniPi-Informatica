#include <stdio.h>

int main (){
	int fib_0 = 0;
	int fib_1 = 1;
	int n, temp;
	scanf("%d", &n);
	do{
		printf("%d\n", fib_0);
		temp = fib_1;
		fib_1 += fib_0;
		fib_0 = temp;
	} while (fib_0 <= n);
	return 0;
}
