#include <stdio.h>

int main(){
	int i;
	int n = 10;
	int array[10];
	for(i = 0; i < n; i++)
		scanf("%d", &array[i]);
	for(i = n-1; i>=0; i--){
		if(array[i]%2 == 0)
			printf("%d\n", array[i]/2);
		else
			printf("%d\n", array[i]);
	}
	return 0;
}
