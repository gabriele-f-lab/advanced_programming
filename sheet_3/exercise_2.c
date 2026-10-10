#include <stdio.h>

int main() {
	
	int n_1, n_2, max_12;

	printf("First number? \n");
	scanf("%d", &n_1);
	printf("Second number? \n");
	scanf("%d", &n_2);

	if (n_1 == n_2) {
		printf("The two numbers are equal\n");
	} else {
		max_12 = n_1 > n_2 ? n_1 : n_2;
		printf("The maximum of the two numbers is %d \n", max_12);	
	}



}
