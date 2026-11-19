#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rho_der(double t, double rho_g);
double var_rho_der(double t, double rho_g);
double rho_analytical(double t);
double var_rho_analytical(double t);
double coupled_rho_analytical(double t);
double coupled_var_rho_analytical(double t);
void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double));
void runge_kutta_g_const(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double));

double c_s = 0.02, rho_g_i = 10., t_g = 1.5, half_step;

// requires the time step and the total time as command line arguments
int main(int argc, char *argv[]) {
	if (argc > 2) {
		int n_step, j, n_step_store;
		double t_max, t_step, *rho_i, *rho_i_4, *t_i, step_store = 0.2; // step_store is the output interval (note: it must be greater or equal to the integration step (t_step))
                                                                        
		t_step = (double) atof(argv[1]);
		t_max = (double) atof(argv[2]);

        half_step = t_step / 2.;
		n_step = (int) floor(t_max / t_step);
		n_step_store = (int) floor(t_max / step_store);
		
		rho_i_4 = (double *) malloc(n_step_store * sizeof(double));
		rho_i = (double *) malloc(n_step_store * sizeof(double));
		t_i = (double *) malloc(n_step_store * sizeof(double));

		runge_kutta_g_const(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, rho_der);
		
		printf("Results with derivative independent of time and constant gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - rho_analytical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - rho_analytical(t_i[j])));
		}

		runge_kutta_g_const(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, var_rho_der);
		
		printf("Results with derivative proportional to time and constant gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - var_rho_analytical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - var_rho_analytical(t_i[j])));
		}

		runge_kutta(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, rho_der);
		
		printf("Results with derivative independent of time and variable gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - coupled_rho_analytical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - coupled_rho_analytical(t_i[j])));
		}

		runge_kutta(n_step, n_step_store, t_step, step_store, rho_i, rho_i_4, t_i, var_rho_der);
		
		printf("Results with derivative proportional to time and variable gas density\n");
		printf("  time   |   rho_2   |  |error|  |   rho_4   |  |error| \n");
		for (j = 0; j < n_step_store; j++) {
			printf("%8.6lf | %9.6lf | %9.3e | %9.6lf | %9.3e\n", t_i[j], rho_i[j], fabs(rho_i[j] - coupled_var_rho_analytical(t_i[j])), rho_i_4[j], fabs(rho_i_4[j] - coupled_var_rho_analytical(t_i[j])));
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

// d rho* / dt independent of t
double rho_der(double t, double rho_g) {
	return c_s * rho_g / t_g;
}

// d rho* / dt linear in t
double var_rho_der(double t, double rho_g) {
	return c_s * rho_g / t_g * t;
}

// analytical solution of rho_der
double rho_analytical(double t) {
	return c_s * rho_g_i / t_g * t;
}

// analytical solution of var_rho_der
double var_rho_analytical(double t) {
	return c_s * rho_g_i / t_g * pow(t, 2.) / 2.;
}

// analytical solution of rho_der where also the gas can vary: d rho_gas / dt = -d rho* / dt
double coupled_rho_analytical(double t) {
	return rho_g_i *(1. - exp(-c_s/t_g * t));
}

// analytical solution of var_rho_der where also the gas can vary: d rho_gas / dt = -d rho* / dt
double coupled_var_rho_analytical(double t) {
	return rho_g_i *(1. - exp(-c_s/(2. * t_g) * pow(t, 2.)));
}

// provide rho* and t every step_store computed both with the midpoint method and the fourth order Runge-Kutta algorithm, assuming a coupled system (d rho_gas / dt = -d rho* / dt)
void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *p_4, double *time, double (*f) (double, double)) {
	double t = 0., k_1, k_2, k_1_4, k_2_4, k_3_4, k_4_4, rho = 0., rho_g = rho_g_i, rho_4 = 0., rho_g_4 = rho_g_i;
	int j = 0;

    // since the derivative of rho_gas with respect to time is minus the one of the rho*, it is not necessary to add other functions for the former:
    // since each quantity depends linearly on f (derivative of rho*), it is sufficient to multiply it by a minus sign when computing quantities related to rho_gas in the following way
	for (int i = 0; i < n_step_1; i++){
		k_1 = step * f(t, rho_g);
		k_2 = step * f(t + 0.5 * step, rho_g - 0.5 * k_1);
		k_1_4 = step * f(t, rho_g_4);
		k_2_4 = step * f(t + 0.5 * step, rho_g_4 - 0.5 * k_1_4);
		k_3_4 = step * f(t + 0.5 * step, rho_g_4 - 0.5 * k_2_4);
		k_4_4 = step * f(t + step, rho_g_4 - k_3_4);
		rho += k_2;
		rho_g -= k_2;
		rho_4 += 1./6. * (k_1_4 + k_4_4) + 1./3. * (k_2_4 + k_3_4);
		rho_g_4 -= 1./6. * (k_1_4 + k_4_4) + 1./3. * (k_2_4 + k_3_4);
		t += step;

        // store rho and t only when the latter is closer to a multiple of step_store than half of the computing step
		if (t >= (step_store_1 * ((double) j + 1.) - half_step) && j < n_step_store_1) {
			p[j] = rho;
			p_4[j] = rho_4;
			time[j] = t;
			j++;
		}
	}
}

// provide rho* and t every step_store computed both with the midpoint method and the fourth order Runge-Kutta algorithm, assuming a non-coupled system (constant rho_gas)
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

        // store rho and t only when the latter is closer to a multiple of step_store than half of the computing step
		if (t >= (step_store_1 * ((double) j + 1.) - half_step) && j < n_step_store_1) {
			p[j] = rho;
			p_4[j] = rho_4;
			time[j] = t;
			j++;
		}
	}
}
