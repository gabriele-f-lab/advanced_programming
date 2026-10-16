#include <stdio.h>
#include <string.h>


void squeeze2(char a[], char b[]);

int main(){
	char st_1[] = "test a 1";
	char st_2[] = " ";

	squeeze2(st_1, st_2);
	printf("%s\n", st_1);

}

void squeeze2 (char a[], char b[]) {
	int cont, n = 0;

	for (int i = 0; a[i] != '\0'; i++) {
		cont = 1;
		for (int j = 0; b[j] != '\0'; j++) {
			if (a[i] == b[j]) {
				cont = 0;
			}
		}
		if (cont == 1) {
			a[n] = a[i];
			n++;
		}
	}
	a[n] = '\0';
}
