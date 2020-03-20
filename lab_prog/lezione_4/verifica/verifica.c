#include <stdio.h>

int main(){
	int i;
	int elem = -1;
	int n = 10;
	int A[10];
	for(i = 0; i < n; i++)
		scanf("%d", &A[i]);
	i = 1;
	while(elem == -1 && i < n-1){
		if(A[i] == A[i+1] - A[i-1])
			elem = i;
		else
			i++;
	}
	printf("%d\n", elem);
}
