#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float rho_der(float t);
float var_rho_der(float t);
void midpoint(float t_end, float step, float *p, float *time, float (*f) (float));

int main(int argc, char *argv[]) {
	if (argc == 3) {
		int n_step;
		float t_max, t_step, *rho_i, *t_i;

		t_step = atof(argv[1]);
		t_max = atof(argv[2]);

		n_step = (int) floor(t_max / t_step);
		rho_i = (float *) malloc(n_step * sizeof(float));
		t_i = (float *) malloc(n_step * sizeof(float));

		midpoint(t_max, t_step, rho_i, t_i, rho_der);
		
		for (int j = 0; j < n_step; j++) {
			printf("Rho at time %f: %f\n", t_i[j], rho_i[j]);
		}

		midpoint(t_max, t_step, rho_i, t_i, var_rho_der);
		
		for (int j = 0; j < n_step; j++) {
			printf("Rho at time %f: %f\n", t_i[j], rho_i[j]);
		}

		free(t_i);
		free(rho_i);
	} else {
		return 0;
	}
}

float rho_der(float t) {
	float c_s = 0.02, rho_g = 10., t_g = 1.5;

	return c_s * rho_g / t_g;
}

float var_rho_der(float t) {
	float c_s = 0.02, rho_g = 10., t_g = 1.5;

	return c_s * rho_g / t_g * t;
}

void midpoint(float t_end, float step, float *p, float *time, float (*f) (float)) {
	float t = 0., k_1, k_2, rho = 0.;
	int i = 0;

	do {
		k_1 = step * f(t);
		k_2 = step * f(t + 0.5 * step);
		rho += k_2;
		p[i] = rho;
		t += step;
		time[i] = t;
		i++;

	} while (t <= t_end);
}
