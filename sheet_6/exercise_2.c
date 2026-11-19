/* Objective:
 * Solve a set of five second degree equations, each of the type:
 * a x^2 + b x + c = 0
 * where a[5], b[5] and c[5] have to be declared as *a, b and *c.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// number of equations to solve
#define NUMB_EQ 5

void solve(double *a_1, double *b_1, double *c_1, int i, double *sols_1);

int main() {
	double *a, *b, *c, *sols;
	int i;
	a = (double *)malloc(NUMB_EQ*sizeof(double));
	b = (double *)malloc(NUMB_EQ*sizeof(double));
	c = (double *)malloc(NUMB_EQ*sizeof(double));
    // there are at most 2 solutions for each equation
	sols = (double *)malloc(2*NUMB_EQ*sizeof(double));

	for (i = 0; i < NUMB_EQ; i++) {
		printf("Insert a, b, c coefficients of equation %d: ", i + 1);
		scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
	}
	
	for (i = 0; i < NUMB_EQ; i++) {
		solve(a, b, c, i, sols);
	}

    printf("Solutions: a value of -999.9 means that there are no real solutions, while -1999.8 indicates an identity\n");
	for (i = 0; i < NUMB_EQ; i++) {
		printf("Solutions of equation %d are : %lf and %lf \n", i + 1, sols[2*i], sols[2*i + 1]);
	}

	free(sols);
	free(c);
	free(b);
	free(a);

	return 0;
}

// fill the two entries corresponding to equation i in sols_1 with its solutions
void solve(double *a_1, double *b_1, double *c_1, int i, double *sols_1) {
	double d, check_id;

	if (a_1[i] == 0) { // in this case the equation is linear: it has one solution (stored twice) if b is nonzero, no solutions if b is zero and c is nonzero, or infinitely many solutions if both b and c are zero
        check_id = c_1[i] == 0. ? 2. : 1.;
		sols_1[2*i] = b_1[i] == 0 ? -999.9*check_id: -c_1[i] / b_1[i];
		sols_1[2*i + 1] = b_1[i] == 0 ? -999.9*check_id : -c_1[i] / b_1[i];
	} else {
		d = pow(b_1[i], 2.) - 4.*a_1[i]*c_1[i];
		if (d < 0) { // if d < 0 there are no real solutions
			sols_1[2*i] = -999.9;
			sols_1[2*i + 1] = -999.9;
		} else {
			sols_1[2*i] = d == 0 ? -b_1[i]/(2.*a_1[i]) : (-b_1[i] - sqrt(d))/(2.*a_1[i]);
			sols_1[2*i + 1] = d == 0 ? -b_1[i]/(2.*a_1[i]) : (-b_1[i] + sqrt(d))/(2.*a_1[i]);
		}
	}
}
