#include <stdio.h>
#include <string.h>

int main() {
	char a[100];
	char tot[1000];

	for (int i = 0; i < 100; i++) {
	       	scanf("%s", a);
		strcat(tot, " ");
		strcat(tot, a);
	}
	
	printf("%s\n", tot);
}
