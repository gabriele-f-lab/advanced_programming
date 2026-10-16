#include <stdio.h>
#include <string.h>
#include <math.h>

int count_digits(int n);

int main(){
	int n;

	for (int i = 0; i < 8; i++) {
		printf("Insert integer number \n");
		scanf("%d", &n);
		printf("Number of digits = %d\n", count_digits(n));
	}
}

int count_digits(int n) {
	return floor(log10(n)) + 1;
}
