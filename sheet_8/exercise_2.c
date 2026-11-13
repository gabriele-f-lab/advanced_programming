#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define inv_s_to_inv_Gyr (86400*365*1e9 / (150e8 * 206265))

double a_der(double t, double a);
void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *time, double (*f) (double, double));

double h_0 = 70, m_0 = 0.3, de_0 = 0.7, w = -1, half_step;

int main(int argc, char *argv[]) {
	if (argc > 3) {
		int n_step, j, n_step_store;
		double t_max, t_step, *a_i, *t_i, step_store = 0.2;

		t_step = (double) atof(argv[1]);
		t_max = (double) atof(argv[2]);

        h_0 *= inv_s_to_inv_Gyr;
        half_step = t_step / 2.;
		n_step = (int) floor(t_max / t_step);
		n_step_store = (int) floor(t_max / step_store);
		
		a_i = (double *) malloc(n_step_store * sizeof(double));
		t_i = (double *) malloc(n_step_store * sizeof(double));

		runge_kutta(n_step, n_step_store, t_step, step_store, a_i, t_i, a_der);
		
		printf("Results with derivative independent of time and variable gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%lf, %lf\n", t_i[j], a_i[j]);
		}

		free(t_i);
		free(a_i);

		return 0;
	} else {
		printf("Missing arguments: insert omega_m_0, omega_DE_0 and w\n");	

		return 0;
	}
}

double a_der(double t, double a) {
	return sqrt(pow(h_0, 2.) * (m_0 * pow(a, -3.) + (1 - m_0 - de_0) * pow(a, -2.) + de_0 * pow(a, 3 * (1 + w))));
}

void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *time, double (*f) (double, double)) {
	double t = 0., k_1, k_2, a = 1.;
	int j = 0;

	for (int i = 0; i < n_step_1; i++){
		k_1 = step * f(t, a);
		k_2 = step * f(t + 0.5 * step, a + 0.5 * k_1);
        a += k_2;        
		t += step;

		if (t >= (step_store_1 * ((double) j + 1.) - half_step) && j < n_step_store_1) {
			p[j] = a;
			time[j] = t;
			j++;
		}
	}
}
