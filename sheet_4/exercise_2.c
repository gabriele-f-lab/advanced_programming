#include <stdio.h>

int main(){

	int n = 0, n_div = 0;

	printf("Insert integer number ");
	scanf("%d", &n);

	for (int i = 1; i < n/2 + 1; i++) {
		if (n%i == 0)
			n_div++;
	}
	if (n_div == 1)
		printf("%d is prime\n", n);
	else
		printf("%d is not prime\n", n);
}
