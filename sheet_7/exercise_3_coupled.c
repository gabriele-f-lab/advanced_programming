#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rho_der(double t, double rho_g);
double var_rho_der(double t, double rho_g);
double rho_analitical(double t);
double var_rho_analitical(double t);
double coupled_rho_analitical(double t);
double coupled_var_rho_analitical(double t);
void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double));
void runge_kutta_g_const(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double));

double c_s = 0.02, rho_g_i = 10., t_g = 1.5;

int main(int argc, char *argv[]) {
	if (argc == 3) {
		int n_step, j, n_step_store;
		double t_max, t_step, *rho_i, *rho_i_4, *t_i, step_store = 0.2;

		t_step = (double) atof(argv[1]);
		t_max = (double) atof(argv[2]);

		n_step = (int) floor(t_max / t_step);
		n_step_store = (int) floor(t_max / step_store);
		
		rho_i_4 = (double *) malloc(n_step_store * sizeof(double));
		rho_i = (double *) malloc(n_step_store * sizeof(double));
		t_i = (double *) malloc(n_step_store * sizeof(double));

		runge_kutta_g_const(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, rho_der);
		
		printf("Results with derivative independent of time and constant gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - rho_analitical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - rho_analitical(t_i[j])));
		}

		runge_kutta_g_const(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, var_rho_der);
		
		printf("Results with derivative proportional to time and constant gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - var_rho_analitical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - var_rho_analitical(t_i[j])));
		}

		runge_kutta(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, rho_der);
		
		printf("Results with derivative independent of time and variable gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - coupled_rho_analitical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - coupled_rho_analitical(t_i[j])));
		}

		runge_kutta(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, var_rho_der);
		
		printf("Results with derivative proportional to time and variable gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - coupled_var_rho_analitical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - coupled_var_rho_analitical(t_i[j])));
		}

		free(t_i);
		free(rho_i);
		free(rho_i_4);

		return 0;
	} else {
		printf("Missing arguments: insert both the time step and the end time\n");	

		return 0;
	}
}

double rho_der(double t, double rho_g) {
	return c_s * rho_g / t_g;
}

double var_rho_der(double t, double rho_g) {
	return c_s * rho_g / t_g * t;
}

double rho_analitical(double t) {
	return c_s * rho_g_i / t_g * t;
}

double var_rho_analitical(double t) {
	return c_s * rho_g_i / t_g * pow(t, 2.) / 2.;
}

double coupled_rho_analitical(double t) {
	return rho_g_i *(1. - exp(-c_s/t_g * t));
}

double coupled_var_rho_analitical(double t) {
	return rho_g_i *(1. - exp(-c_s/(2. * t_g) * pow(t, 2.)));
}

void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double)) {
	double t = 0., k_1, k_2, k_3, k_4, rho = 0., rho_g = rho_g_i, rho_4 = 0., rho_g_4 = rho_g_i;
	int j = 0;

	for (int i = 0; i < n_step_1; i++){
		k_1 = step * f(t, rho_g);
		k_2 = step * f(t + 0.5 * step, rho_g - 0.5 * k_1);
		k_3 = step * f(t + 0.5 * step, rho_g - 0.5 * k_2);
		k_4 = step * f(t + step, rho_g - k_3);
		rho += k_2;
		rho_g -= k_2;
		rho_4 += 1./6. * (k_1 + k_4) + 1./3. * (k_2 + k_3);
		rho_g_4 -= 1./6. * (k_1 + k_4) + 1./3. * (k_2 + k_3);
		t += step;

		if (t >= (step_store_1 * ((double) j + 1) - 0.01) && j < n_step_store_1) {
			p[j] = rho;
			p_4[j] = rho_4;
			time[j] = t;
			j++;
		}
	}
}

void runge_kutta_g_const(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double)) {
	double t = 0., k_1, k_2, k_4, rho = 0., rho_4 = 0.;
	int j = 0;

	for (int i = 0; i < n_step_1; i++){
		k_1 = step * f(t, rho_g_i);
		k_2 = step * f(t + 0.5 * step, rho_g_i);
		k_4 = step * f(t + step, rho_g_i);
		rho += k_2;
		rho_4 += 1./6. * (k_1 + k_4) + 2./3. * k_2;
		t += step;

		if (t >= (step_store_1 * ((double) j + 1) - 0.01) && j < n_step_store_1) {
			p[j] = rho;
			p_4[j] = rho_4;
			time[j] = t;
			j++;
		}
	}
}
