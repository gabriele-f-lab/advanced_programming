#include <stdio.h>
#include <math.h>

typedef struct {
	float func;
	float d_func;
} func_and_der;

func_and_der cubic_eq(float x);
func_and_der trascendental_eq(float y);
void newton_method(float vec[], int n, int max_it, float start_p, float stop_p, float prec, func_and_der (*f) (float));
int sort_vec(float vec[], float prec, int dim);

int main(int argc, char *argv[]) {
	int n_step = 10, n_roots, n_max = 1000;
	float res, precision = 0.00001, p_0_min = -10., p_0_max = 10., p[n_step];

	if (argc == 2) {
		switch (argv[1][0]) {
		case 'c':
			newton_method(p, n_step, n_max, p_0_min, p_0_max, precision, cubic_eq);
			break;
		case 't':
			newton_method(p, n_step, n_max, p_0_min, p_0_max, precision, trascendental_eq);
			break;
		default:
			printf("No function selected, insert 't' or 'c' \n");
			return 0;
		}	
		n_roots = sort_vec(p, precision, n_step);

		printf("Number of roots: %d\n", n_roots);
		for (int j = 0; j < n_roots; j++) {
			printf("Root %d: %f\n", j + 1, p[j]);
		}

		return 0;
	} else {
		printf("No argument passed\n");

		return 0;
	}
}

func_and_der cubic_eq(float x) {
	func_and_der a;
	a.func = pow(x, 3.) + x + 1.;
	a.d_func = 3.*pow(x, 2.) + 1.;
	
	return a;
}

func_and_der trascendental_eq(float y) {
	func_and_der b;
	b.func = exp(y) - 3.*y;
	b.d_func = exp(y) - 3.;
	
	return b;
}

void newton_method(float vec[], int n, int max_it, float start_p, float stop_p, float prec, func_and_der (*f) (float)) {
	float x, delta, d_x = (stop_p - start_p) / ((float) n);
	int cont;

	for (int i = 0; i < n; i++) {
		x = start_p + (float) i * d_x;
		cont = 0;

		do {
			delta = x;
			x = x - f(x).func / f(x).d_func;
			delta = x - delta;
			cont++;
		} while (fabs(delta) > prec && cont < max_it);
		vec[i] = x;
	}
}

int sort_vec(float vec[], float prec, int dim) {
	int check, not_rep = 0, i;
	
	for (i = 0; i < dim; i++) {
		check = 1;
		for (int j = 0; j < not_rep; j++) {
			if (fabs(vec[j] - vec[i]) < prec) {
				check = 0;
			}
		}
		if (check == 1) {
			vec[not_rep] = vec[i];
			not_rep++;
		}
	}	
	for (i = not_rep; i < dim; i++) vec[i] = 0;

	return not_rep;
}
