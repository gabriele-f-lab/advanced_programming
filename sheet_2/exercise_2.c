#include <stdio.h>

int main(){
	int A;
	int B;
	int C;

	printf("First value ");
	scanf("%d", &A);
	printf("Second value ");
	scanf("%d", &B);

	C=A;
	A=B;
	B=C;

	printf("A= %d, B= %d", A, B);

	return 0;
}
