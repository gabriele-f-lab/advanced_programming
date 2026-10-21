#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double square_root(double a, double prec);

int main(){
	double n = 10000;

	for (int i = 0; i < 10; i++) {
		square_root(n, pow(10, -i));
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

	printf("Precision: %.10lf, number of iterations: %d, square root: %lf\n", prec, cont, x);
	return 0;
}
