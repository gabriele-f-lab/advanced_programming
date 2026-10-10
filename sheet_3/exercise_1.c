#include <stdio.h>

int main(){
	/*
	int a, parity;

	printf("number? ");
	scanf("%d", &a);

	parity = a%2 == 0 ? 1 : 0;

	printf("%d (1 = even, 0 = odd)\n", parity);
	*/

	int a;
	char parity[1] = "d";
	char even[1] = "e", odd[1] = "o";
	
	printf("number? ");
	scanf("%d", &a);

	//parity = a%2 == 0 ? even : odd;
	
	if (a%2 == 0) {
		printf("Even\n");
	} else {
		printf("Odd\n");
	}

	//printf("%d (1 = even, 0 = odd)\n", parity);


}
