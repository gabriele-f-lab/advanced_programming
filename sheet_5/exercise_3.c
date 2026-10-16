#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double square_root(double a, double prec);

int main(){
	double n;
	double m = 0.0001;

	for (int i = 0; i < 8; i++) {
		printf("Insert float number \n");
		scanf("%lf", &n);
		printf("The square root of %lf is = %.4lf\n", n, square_root(n, m));
	}
}


double square_root(double a, double prec) {
	double x = a, delta;
	int cont = 0;

	do {
		delta = x;
		x = 0.5 * (x + a / x);
		delta = delta - x;
		cont++;
	} while (delta > prec);

	printf("Number of iterations: %d\n", cont);
	return x;
}
