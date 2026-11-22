#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_GRID 340

int x_left = 5, x_right = 55;
double vel = 5., half_step;

void initialize_grid (double *p);
void exact_s(int n_step_store_1, double step_store_1, double t_max_1, double *p, FILE *f);
void ftcs   (int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g);
void lax    (int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g);
void upwind1(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g);
void upwind2(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g);
void lax_w  (int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g);
double errors (double *vec);

int main (int argc, char *argv[]) {
    double x[N_GRID], t_step = 0.04, t_step_store = 0.2, t_max = 25.;
    int n_step, n_step_store, run[5], i = 1, j, k, read = 0, check_values[3], tot = 0, n_int_plot = 4, plot_ratio;
    FILE *fp, *gp;
    char str[100] = "", c;

    for (int s = 0; s < 5; s++) run[s] = 0;
    for (int s = 0; s < 3; s++) check_values[s] = 0;

    if (argc > 1) {
        k = argc - 1;
        while (k > 0) {
            if (argv[i][0] == '-') {
                j = 1;
                strcpy(str, "");
                while (c = argv[i][j]) {
                    char temp[2] = {c, '\0'};
                    strcat(str, temp);
                    j++;
                }
                if      (strcmp(str, "all") == 0) for (int i = 0; i < 5; i++) run[i] = 1;
                else if (strcmp(str, "ftcs") == 0)    run[0] = 1;
                else if (strcmp(str, "lax") == 0)     run[1] = 1;
                else if (strcmp(str, "upwind1") == 0) run[2] = 1;
                else if (strcmp(str, "upwind2") == 0) run[3] = 1;
                else if (strcmp(str, "lax_w") == 0)   run[4] = 1;
                else if (strcmp(str, "t_step") == 0)  read   = 1;
                else if (strcmp(str, "t_max") == 0)   read   = 2;
                else if (strcmp(str, "t_store") == 0) read   = 3;
                else {
                    printf("Illegal argument\n");
                    return 1;
                }
                if (read != 0) {
                    if (k <= 1 || argv[i+1][0] == '-') {
                        printf("Missing value\n");
                        return 1;
                    }
                    i++;
                    k--;
                    j = 0;
                    strcpy(str, "");
                    while (c = argv[i][j]) {
                        char temp[2] = {c, '\0'};
                        strcat(str, temp);
                        j++;
                    }
                    switch (read) {
                        case 1:
                            t_step = atof(str);
                            check_values[0] = 1;
                            break;
                        case 2:
                            t_max = atof(str);
                            check_values[1] = 1;
                            break;
                        case 3:
                            t_step_store = atof(str);
                            check_values[2] = 1;
                            break;
                    }
                    read = 0;
                }
                
                i++;
            } else {
                printf("Illegal argument\n");
                return 1;
            }
            k--;
        }
    }

    if (check_values[0] == 0) printf("timestep not provided, a default value of %lf is used\n", t_step);
    if (check_values[1] == 0) printf("end time not provided, a default value of %lf is used\n", t_max);
    if (check_values[2] == 0) printf("output timestep not provided, a default value of %lf is used\n", t_step_store);

    n_step = (int) floor(t_max / t_step);
    n_step_store = (int) floor(t_max / t_step_store) + 1;
    plot_ratio = (int) floor((float) n_step_store / (float) n_int_plot);

    half_step = t_step / 2.;
    fp = fopen("output.txt", "w");
    gp = fopen("errors.txt", "w");

    initialize_grid(x);

    for (int i = 0; i < 5; i++)
        tot += run[i];

    fprintf(fp, "%d\n", tot);
    fprintf(fp, "%d\n", plot_ratio);

    exact_s (n_step_store, t_step_store, t_max, x, fp);
    if (run[0] == 1) ftcs   (n_step, n_step_store, t_step, t_step_store, x, fp, gp);
    if (run[1] == 1) lax    (n_step, n_step_store, t_step, t_step_store, x, fp, gp);
    if (run[2] == 1) upwind1(n_step, n_step_store, t_step, t_step_store, x, fp, gp);
    if (run[3] == 1) upwind2(n_step, n_step_store, t_step, t_step_store, x, fp, gp);
    if (run[4] == 1) lax_w  (n_step, n_step_store, t_step, t_step_store, x, fp, gp);

    fprintf(fp, "end\n");

    fclose(fp);

    return 0;
}

void initialize_grid (double *p) {
    for (int i = 0; i < N_GRID; i++)
        p[i] = (i >= x_left && i <= x_right) ? 1. : 0.;
}

void exact_s(int n_step_store_1, double step_store_1, double t_max_1, double *p, FILE *f) {
    double t, val;
    int last = 0;

    fprintf(f, "exact\n");
    for (int j = 0; j < n_step_store_1; j++) {
        t = step_store_1 * ((double) j);
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            val = (k >= x_left + t * vel && k <= x_right + t * vel) ? 1. : 0.;
            fprintf(f, " %lf ", val);
        }
        fprintf(f, "\n");
    }
    if (t < t_max_1) {
        fprintf(f, "%lf\n", t_max_1);
        for (int k = 0; k < N_GRID; k++) {
            val = (k >= x_left + t_max_1 * vel && k <= x_right + t_max_1 * vel) ? 1. : 0.;
            fprintf(f, " %lf ", val);
        }
        fprintf(f, "\n");
    }
}

void ftcs(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g) {
	double t = 0., p_temp[N_GRID], p_temp_1[N_GRID], c = vel * step, e;
	int j = 1, last = 0;

    fprintf(f, "ftcs\n");
    fprintf(g, "ftcs\n");

    fprintf(f, "%lf\n", t);
    for (int k = 0; k < N_GRID; k++) {
        fprintf(f, " %lf ", p[k]);
        p_temp[k] = p_temp_1[k] = p[k];
    }
    fprintf(f, "\n");

	for (int i = 0; i < n_step_1; i++) {
        for (int k = 1; k < N_GRID - 1; k++) {
            p_temp[k] = p_temp_1[k] - c / 2. * (p_temp_1[k+1] - p_temp_1[k-1]);
        }
        p_temp[0] = p_temp_1[0] - c / 2. * (p_temp_1[1] - p_temp_1[0]);
        p_temp[N_GRID-1] = p_temp_1[N_GRID-1] - c / 2. * (p_temp_1[N_GRID-1] - p_temp_1[N_GRID-2]);
        t += step;

        last = 0;
		if (t >= (step_store_1 * ((double) j) - half_step) && j < n_step_store_1) {
            fprintf(f, "%lf\n", t);
            for (int k = 0; k < N_GRID; k++) {
                fprintf(f, " %lf ", p_temp[k]);
            }
            e = errors (p_temp);
            fprintf(g, "%lf %lf\n", t, e);
            fprintf(f, "\n");
			j++;
            last = 1;
		}
        for (int k = 0; k < N_GRID; k++)
            p_temp_1[k] = p_temp[k];
	}
    if (last == 0) {
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            fprintf(f, " %lf ", p_temp[k]);
        }
        fprintf(f, "\n");
    }
}

void lax(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g) {
	double t = 0., p_temp[N_GRID], p_temp_1[N_GRID], c = vel * step, e;
	int j = 1, last = 0;

    fprintf(f, "lax\n");
    fprintf(g, "lax\n");

    fprintf(f, "%lf\n", t);
    for (int k = 0; k < N_GRID; k++) {
        fprintf(f, " %lf ", p[k]);
        p_temp[k] = p_temp_1[k] = p[k];
    }
    fprintf(f, "\n");

	for (int i = 0; i < n_step_1; i++) {
        for (int k = 1; k < N_GRID - 1; k++) {
            p_temp[k] = (p_temp_1[k+1] + p_temp_1[k-1]) / 2. - c / 2. * (p_temp_1[k+1] - p_temp_1[k-1]);
        }
        p_temp[0] = (p_temp_1[1] + p_temp_1[0]) / 2. - c / 2. * (p_temp_1[1] - p_temp_1[0]);
        p_temp[N_GRID-1] = (p_temp_1[N_GRID-1] + p_temp_1[N_GRID-2]) / 2. - c / 2. * (p_temp_1[N_GRID-1] - p_temp_1[N_GRID-2]);
        t += step;

        last = 0;
		if (t >= (step_store_1 * ((double) j) - half_step) && j < n_step_store_1) {
            fprintf(f, "%lf\n", t);
            for (int k = 0; k < N_GRID; k++) {
                fprintf(f, " %lf ", p_temp[k]);
            }
            e = errors (p_temp);
            fprintf(g, "%lf %lf\n", t, e);
            fprintf(f, "\n");
			j++;
            last = 1;
		}
        for (int k = 0; k < N_GRID; k++)
            p_temp_1[k] = p_temp[k];
	}
    if (last == 0) {
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            fprintf(f, " %lf ", p_temp[k]);
        }
        fprintf(f, "\n");
    }
}

void upwind1(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g) {
	double t = 0., p_temp[N_GRID], p_temp_1[N_GRID], c = vel * step, e;
	int j = 1, last = 0;

    fprintf(f, "upwind1\n");
    fprintf(g, "upwind1\n");

    fprintf(f, "%lf\n", t);
    for (int k = 0; k < N_GRID; k++) {
        fprintf(f, " %lf ", p[k]);
        p_temp[k] = p_temp_1[k] = p[k];
    }
    fprintf(f, "\n");

	for (int i = 0; i < n_step_1; i++) {
        for (int k = 1; k < N_GRID - 1; k++) {
            p_temp[k] = vel >= 0 ? p_temp_1[k] - c * (p_temp_1[k] - p_temp_1[k-1]) : p_temp_1[k] - c * (p_temp_1[k+1] - p_temp_1[k]);
        }
        p_temp[0] = vel >= 0 ? p_temp_1[0] : p_temp_1[0] - c * (p_temp_1[1] - p_temp_1[0]);
        p_temp[N_GRID-1] = vel >= 0 ? p_temp_1[N_GRID-1] - c * (p_temp_1[N_GRID-1] - p_temp_1[N_GRID-2]) : p_temp_1[N_GRID-1];
        t += step;

        last = 0;
		if (t >= (step_store_1 * ((double) j) - half_step) && j < n_step_store_1) {
            fprintf(f, "%lf\n", t);
            for (int k = 0; k < N_GRID; k++) {
                fprintf(f, " %lf ", p_temp[k]);
            }
            e = errors (p_temp);
            fprintf(g, "%lf %lf\n", t, e);
            fprintf(f, "\n");
			j++;
            last = 1;
		}
        for (int k = 0; k < N_GRID; k++)
            p_temp_1[k] = p_temp[k];
	}
    if (last == 0) {
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            fprintf(f, " %lf ", p_temp[k]);
        }
        fprintf(f, "\n");
    }
}

void upwind2(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g) {
	double t = 0., p_temp[N_GRID], p_temp_1[N_GRID], c = vel * step, e;
	int j = 1, last = 0;

    fprintf(f, "upwind2\n");
    fprintf(g, "upwind2\n");

    fprintf(f, "%lf\n", t);
    for (int k = 0; k < N_GRID; k++) {
        fprintf(f, " %lf ", p[k]);
        p_temp[k] = p_temp_1[k] = p[k];
    }
    fprintf(f, "\n");

	for (int i = 0; i < n_step_1; i++) {
        for (int k = 2; k < N_GRID - 2; k++) {
            p_temp[k] = vel >= 0 ? p_temp_1[k] - c / 2. * (3. * p_temp_1[k] - 4. * p_temp_1[k-1] + p_temp_1[k-2]) : p_temp_1[k] + c / 2. * (3. * p_temp_1[k] - 4. * p_temp_1[k+1] + p_temp_1[k+2]);
        }
        p_temp[0] = vel >= 0 ? p_temp_1[0] : p_temp_1[0] + c / 2. * (3. * p_temp_1[0] - 4. * p_temp_1[1] + p_temp_1[2]);
        p_temp[1] = vel >= 0 ? p_temp_1[1] - c / 2. * (3. * p_temp_1[1] - 4. * p_temp_1[0] + p_temp_1[0]) : p_temp_1[1] + c / 2. * (3. * p_temp_1[1] - 4. * p_temp_1[2] + p_temp_1[3]);
        p_temp[N_GRID-2] = vel >= 0 ? p_temp_1[N_GRID-2] - c / 2. * (3. * p_temp_1[N_GRID-2] - 4. * p_temp_1[N_GRID-3] + p_temp_1[N_GRID-4]) : p_temp_1[N_GRID-2] + c / 2. * (3. * p_temp_1[N_GRID-2] - 4. * p_temp_1[N_GRID-1] + p_temp_1[N_GRID-1]);
        p_temp[N_GRID-1] = vel >= 0 ? p_temp_1[N_GRID-1] - c / 2. * (3. * p_temp_1[N_GRID-1] - 4. * p_temp_1[N_GRID-2] + p_temp_1[N_GRID-3]) : p_temp_1[N_GRID-1];
        t += step;

        last = 0;
		if (t >= (step_store_1 * ((double) j) - half_step) && j < n_step_store_1) {
            fprintf(f, "%lf\n", t);
            for (int k = 0; k < N_GRID; k++) {
                fprintf(f, " %lf ", p_temp[k]);
            }
            e = errors (p_temp);
            fprintf(g, "%lf %lf\n", t, e);
            last = 1;
            fprintf(f, "\n");
			j++;
		}
        for (int k = 0; k < N_GRID; k++)
            p_temp_1[k] = p_temp[k];
    }        
    if (last == 0) {
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            fprintf(f, " %lf ", p_temp[k]);
        }
        fprintf(f, "\n");
    }
}

void lax_w(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, FILE *f, FILE *g) {
	double t = 0., p_temp[N_GRID], p_temp_1[N_GRID], c = vel * step, e;
	int j = 1, last = 0;

    fprintf(f, "lax_w\n");
    fprintf(g, "lax_w\n");

    fprintf(f, "%lf\n", t);
    for (int k = 0; k < N_GRID; k++) {
        fprintf(f, " %lf ", p[k]);
        p_temp[k] = p_temp_1[k] = p[k];
    }
    fprintf(f, "\n");

	for (int i = 0; i < n_step_1; i++) {
        for (int k = 1; k < N_GRID - 1; k++) {
            p_temp[k] = p_temp_1[k] - c / 2. * (p_temp_1[k+1] - p_temp_1[k-1]) + c*c / 2. * (p_temp_1[k+1] + p_temp_1[k-1] - 2. * p_temp_1[k]);
        }
        p_temp[0] = p_temp_1[0] - c / 2. * (p_temp_1[1] - p_temp_1[0]) + c*c / 2. * (p_temp_1[1] + p_temp_1[0] - 2. * p_temp_1[0]);
        p_temp[N_GRID-1] = p_temp_1[N_GRID-1] - c / 2. * (p_temp_1[N_GRID-1] - p_temp_1[N_GRID-2]) + c*c / 2. * (p_temp_1[N_GRID-1] + p_temp_1[N_GRID-2] - 2. * p_temp_1[N_GRID-1]);
        t += step;

        last = 0;
		if (t >= (step_store_1 * ((double) j) - half_step) && j < n_step_store_1) {
            fprintf(f, "%lf\n", t);
            for (int k = 0; k < N_GRID; k++) {
                fprintf(f, " %lf ", p_temp[k]);
            }
            e = errors (p_temp);
            fprintf(g, "%lf %lf\n", t, e);
            fprintf(f, "\n");
			j++;
            last = 1;
		}
        for (int k = 0; k < N_GRID; k++)
            p_temp_1[k] = p_temp[k];
	}
    if (last == 0) {
        fprintf(f, "%lf\n", t);
        for (int k = 0; k < N_GRID; k++) {
            fprintf(f, " %lf ", p_temp[k]);
        }
        fprintf(f, "\n");
    }
}

double errors (double *vec) {
    double err = 0;

    for (int k = 0; k < N_GRID; k++) {
        err += fabs(vec[k]);
    }

    return err;
}
