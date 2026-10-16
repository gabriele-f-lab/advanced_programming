#include <stdio.h>

int main(){
	int n = 0, i = 1, val = 1;

	printf("Insert integer number ");
	scanf("%d", &n);

	while (i <= n) {
		val = val * i;	
		i++;
	}

	printf("The factorial of %d is %d\n", n, val);
}
