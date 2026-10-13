#include <stdio.h>

int product(int n1, int n2) {
	printf("a=%d, b=%d\n", n1, n2);
	if (n2 == 0) return 0;
	return product(n1, n2 - 1) + n1;

}

int main(){
	int a, b, c;

	printf("Insert two integers\n");
	scanf("%d\n %d", &a, &b);

	printf("The product of %d and %d is %d \n", a, b, product(a, b));
}
