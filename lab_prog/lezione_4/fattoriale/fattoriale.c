#include <stdio.h>

int main(){
	int x, i;
	int fattoriale = 1;
	scanf("%d", &x);
	for(i = 2; i <= x; i++)
		fattoriale *= i;
	printf("%d\n", fattoriale);
	return 0;
}
