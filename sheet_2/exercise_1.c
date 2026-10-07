#include <stdio.h>

int main(){
	int A;
	int B;
	int C;

	printf("First value ");
	scanf("%d", &A);
	printf("Second value ");
	scanf("%d", &B);
	printf("Third value ");
	scanf("%d", &C);

	printf("A - B = %d\n", A-B);
	printf("A - B + C = %d\n", A-B+C);
	printf("A - B + C + C = %d\n", A-B+2*C);

	return 0;
}
