#include <stdio.h>

int fact(int n){
	int val = 1;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

int main(){
	int m = 0;

	printf("Insert integer number ");
	scanf("%d", &m);

	int val_func = fact(m);
	printf("The factorial of %d is %d (computed using a function)\n", m, val_func);
}
