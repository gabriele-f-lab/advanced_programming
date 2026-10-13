#include <stdio.h>

int fact(int n){
	int val = 1;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

int main(){
	int n = 0, i = 1, val = 1;

	printf("Insert integer number ");
	scanf("%d", &n);

	while (i <= n) {
		val = val * i;	
		i++;
	}

	printf("The factorial of %d is %d\n", n, val);
	int val_func = fact(n);
	printf("The factorial of %d is %d (computed using a function)\n", n, val_func);
}
