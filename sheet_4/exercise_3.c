#include <stdio.h>

int main(){
	int n = 0;

	printf("Insert the number of * ");
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("*");			
		}
		printf("\n");
	}

}
