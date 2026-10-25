#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rho_der(double t);
double var_rho_der(double t);
double rho_analitical(double t);
double var_rho_analitical(double t);
void midpoint(int n_step_1, double step, double step_store_1, double *p, double *time, double (*f) (double));

double c_s = 0.02, rho_g = 10., t_g = 1.5;

int main(int argc, char *argv[]) {
	if (argc == 3) {
		int n_step, j, n_step_store;
		double t_max, t_step, *rho_i, *t_i, step_store = 0.2;

		t_step = (double) atof(argv[1]);
		t_max = (double) atof(argv[2]);

		n_step = (int) floor(t_max / t_step);
		n_step_store = (int) floor(t_max / step_store);
		
		rho_i = (double *) malloc(n_step_store * sizeof(double));
		t_i = (double *) malloc(n_step_store * sizeof(double));

		midpoint(n_step, t_step, step_store, rho_i, t_i, rho_der);
		
		for (j = 0; j < n_step_store; j++) {
			printf("Rho at time %lf: %lf, analitical rho: %lf, absolute difference: %lf\n", t_i[j], rho_i[j], rho_analitical(t_i[j]), fabs(rho_i[j] - rho_analitical(t_i[j])));
		}

		midpoint(n_step, t_step, step_store, rho_i, t_i, var_rho_der);
		
		for (j = 0; j < n_step_store; j++) {
			printf("Rho at time %lf: %lf, analitical rho: %lf, absolute difference: %lf\n", t_i[j], rho_i[j], var_rho_analitical(t_i[j]), fabs(rho_i[j] - var_rho_analitical(t_i[j])));
		}

		free(t_i);
		free(rho_i);

		return 0;
	} else {
		return 0;
	}
}

double rho_der(double t) {
	return c_s * rho_g / t_g;
}

double rho_analitical(double t) {
	return c_s * rho_g / t_g * t;
}

double var_rho_der(double t) {
	return c_s * rho_g / t_g * t;
}

double var_rho_analitical(double t) {
	return c_s * rho_g / t_g * pow(t, 2.) / 2.;
}

void midpoint(int n_step_1, double step, double step_store_1, double *p, double *time, double (*f) (double)) {
	double t = 0., k_1, k_2, rho = 0.;
	int j = 0;

	for (int i = 0; i < n_step_1; i++){
		k_1 = step * f(t);
		k_2 = step * f(t + 0.5 * step);
		rho += k_2;
		t += step;

		if (t >= step_store_1 * ((double) j + 1)) {
			p[j] = rho;
			time[j] = t;
			j++;
		}
	}
}
