#include <stdio.h>

int main(){
	int n, i;
	scanf("%d", &n);
	for(; n >= 1; n-=2){
		for(i = 0; i < n; i++)
			printf("*");
		printf("\n");
	}
	return 0;
}
