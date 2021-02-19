#include <stdio.h>

int main(){
	int i;
	int n = 10;
	int A[10];
	for(i = 0; i < n; i++)
		scanf("%d", &A[i]);
	for(i = 0; i < n; i++){
		if(A[i] >= 0 && A[i]%2 == 0)
			printf("%d\n", A[i]);
		else if(i < n-1 && A[i] < 0  && A[i+1] >= 0)
			printf("%d\n", A[i]);			
	}
	return 0;
}
