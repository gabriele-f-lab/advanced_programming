#include <stdio.h>

int main(){
	int i = 0, j = 0, k = 0, threshold = 20;

	for (;;) {
		printf("%d\n", i);
		i++;
		if (i > threshold)
			break;
	}

	while (1) {
		printf("%d\n", j);
		j++;
		if (j > threshold)
			break;
	}
	
	do {
		printf("%d\n", k);
		k++;
		if (k > threshold)
			break;
	} while (1);

}
