#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define numb_eq 5

void solve(double *a_1, double *b_1, double *c_1, int i, double *sols_1);

int main() {
	double *a, *b, *c, *sols;
	int i;
	a = (double *)malloc(numb_eq*sizeof(double));
	b = (double *)malloc(numb_eq*sizeof(double));
	c = (double *)malloc(numb_eq*sizeof(double));
	sols = (double *)malloc(2*numb_eq*sizeof(double));

	for (i = 0; i < numb_eq; i++) {
		printf("Insert a, b, c coefficients of equation %d: ", i + 1);
		scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
	}
	
	for (i = 0; i < numb_eq; i++) {
		solve(a, b, c, i, sols);
	}

	for (i = 0; i < numb_eq; i++) {
		printf("Solutions of equation %d are: %lf and %lf \n", i + 1, sols[2*i], sols[2*i + 1]);
	}

	free(sols);
	free(c);
	free(b);
	free(a);

	return 0;
}

void solve(double *a_1, double *b_1, double *c_1, int i, double *sols_1) {
	double d;

	if (a_1[i] == 0) {
		sols_1[2*i] = b_1[i] == 0 ? -999.9 : -c_1[i] / b_1[i];
		sols_1[2*i + 1] = b_1[i] == 0 ? -999.9 : -c_1[i] / b_1[i];
	} else {
		d = pow(b_1[i], 2.) - 4.*a_1[i]*c_1[i];
		if (d < 0) {
			sols_1[2*i] = -999.9;
			sols_1[2*i + 1] = -999.9;
		} else {
			sols_1[2*i] = d == 0 ? -b_1[i]/(2.*a_1[i]) : (-b_1[i] - sqrt(d))/(2.*a_1[i]);
			sols_1[2*i + 1] = d == 0 ? -b_1[i]/(2.*a_1[i]) : (-b_1[i] + sqrt(d))/(2.*a_1[i]);
		}
	}
}
