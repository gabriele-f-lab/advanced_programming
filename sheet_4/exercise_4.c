#include <stdio.h>

int main(){
	int n = 0;

	while (1) {
		printf("insert integer number ");
		scanf("%d", &n);

		if (n < 0)
			break;
		printf("%d\n", n);
	}

}
