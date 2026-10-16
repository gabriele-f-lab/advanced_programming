#include <stdio.h>
#include <math.h>

int main(){

	int n = 0, n_div = 0, prime = 1;

	printf("Insert integer number greater than 1 ");
	scanf("%d", &n);

	for (int i = 2; i < pow(n, 0.5) + 1; i++) {
		if (n%i == 0) {
			prime = 0;
			break;	
		}
	}

	if (prime)
		printf("%d is prime\n", n);
	else
		printf("%d is not prime\n", n);
}
