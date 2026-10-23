#include <stdio.h>
#include <math.h>

double cubic_eq(double x, double prec, int n_max);
double trascendental_eq(double x, double prec, int n_max);

int main(int argc, char *argv[]) {
	int n_step = 10, n_max = 1000;
	double res, precision = 0.00001, x_start = 1.;

	if (argc == 2) {
		switch (argv[1][0]) {
		case 'c':
			res = cubic_eq(x_start, precision, n_max);
			break;
		case 't':
			res = trascendental_eq(x_start, precision, n_max);
			break;
		default:
			printf("No function selected, insert 't' or 'c' \n");
			return 0;
		}	

		printf("The root is: %lf\n", res);

		return 0;
	} else {
		printf("No argument passed\n");

		return 0;
	}
}

double cubic_eq(double x, double prec, int n_max) {
	double func, d_func, delta;
	int cont = 0;

	do {
		func = pow(x, 3.) + x + 1.;
		d_func = 3.*pow(x, 2.) + 1.;
		delta = x;
		x = x - func / d_func;
		delta = x - delta;
		cont++;
	} while (fabs(delta) > prec && cont < n_max);

	return x;
}

double trascendental_eq(double x, double prec, int n_max) {
	double func, d_func, delta;
	int cont = 0;

	do {
		func = exp(x) - 3.*x;
		d_func = exp(x) - 3.;
		delta = x;
		x = x - func / d_func;
		delta = x - delta;
		cont++;
	} while (fabs(delta) > prec && cont < n_max);

	return x;

}
