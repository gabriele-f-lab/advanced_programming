#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define inv_s_to_inv_Gyr (86400.*365.25*1e9 / (150e6 * 206265. * 1e6))
#define n_args 6
#define max_len 100

double a_der(double t, double a);
void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *time, double (*f) (double, double));

double h_0 = 70, m_0, de_0, w, half_step;
int collapse = 1;

int main(int argc, char *argv[]) {
    FILE *fp;
    int n_step, j, n_step_store, check[n_args], a, new_file, k = 0;
    double t_max = 14., t_step, *a_i, *t_i, step_store = 0.2;
    char *numb, *header, name[max_len] = "data_";

    h_0 *= inv_s_to_inv_Gyr;
   
    do {
        collapse = 1;
        strcpy(name, "data_");
        new_file = 0;
        for (a = 0; a < n_args; a++)
            check[a] = 0;

        if (argc - 1 - k * 13 >= 12) {
            for (int i = 13 * k + 1; i < 1 + 13 * (k+1) && i < argc; i += 2) {
                switch (argv[i][0]) {
                    case 'm':
                        m_0 = (double) atof(argv[i+1]);
                        check[0] = 1;
                        break;
                    case 'w':
                        w = (double) atof(argv[i+1]);
                        check[1] = 1;
                        break;
                    case 'd':
                        de_0 = (double) atof(argv[i+1]);
                        check[2] = 1;
                        break;
                    case 't':
                        t_step = (double) atof(argv[i+1]);
                        check[3] = 1;
                        break;
                    case 'o':
                        numb = argv[i+1];
                        check[4] = 1;
                        break;
                    case 'h':
                        header = argv[i+1];
                        check[5] = 1;
                        break;
                    case ',':
                        new_file = 1;
                        break;
                    default:
                        printf("Invalid arguments\n");
                        printf("Select the constant to insert with m for omega_m_0, d for omega_DE_0, w for the Eos parameter, t for the time step, o for the file number (file names are like data_i.txt where i is an integer and h for the header of the file, which will be used as legend in the plot, and insert its value as the following argument\n");
                        return 1;
                    i++;
                }
                if (new_file == 1) break;
            }
        } else {
            printf("Missing arguments: insert omega_m_0, omega_DE_0, w, the time step, the file number and its header\n");	
            printf("Select the constant to insert with m for omega_m_0, d for omega_DE_0, w for the Eos parameter, t for the time step, o for the file number (file names are like data_i.txt where i is an integer and h for the header of the file, which will be used as legend in the plot, and insert its value as the following argument\n");
            return 1;
        }

        for (a = 0; a < n_args; a++) {
            check[0] *= check[a];
        }
        if (check[0] == 0) {
            printf("Missing arguments: insert omega_m_0, omega_DE_0, w, the time step, the file number and its header\n");	
            printf("Select the constant to insert with m for omega_m_0, d for omega_DE_0, w for the Eos parameter, t for the time step, o for the file number (file names are like data_i.txt where i is an integer and h for the header of the file, which will be used as legend in the plot, and insert its value as the following argument\n");
            return 1;
        }
        
        strcat(name, numb);
        strcat(name, ".txt");

        fp = fopen(name, "w");
        fprintf(fp, "%s\n", header);

        half_step = t_step / 2.;
        n_step = (int) floor(t_max / t_step);
        n_step_store = (int) floor(t_max / step_store);
        
        a_i = (double *) malloc(n_step_store * sizeof(double));
        t_i = (double *) malloc(n_step_store * sizeof(double));

        runge_kutta(n_step, n_step_store, t_step, step_store, a_i, t_i, a_der);

        
        for (j = 0; j < n_step_store; j++) {
            fprintf(fp, "%lf %lf\n", t_i[j], a_i[j]);
        }

        fclose(fp);

        free(t_i);
        free(a_i);

        k++;
    } while (new_file == 1);

    return 0;
}

double a_der(double t, double a) {
    double val = pow(h_0, 2.) * (m_0 * pow(a, -3.) + (1 - m_0 - de_0) * pow(a, -2.) + de_0 * pow(a, -3 * (1 + w)));
    if (val < 0)
        collapse = collapse == 1 ? -1 : collapse;
	return collapse * a * sqrt(fabs(val));
}

void runge_kutta(int n_step_1, int n_step_store_1, double step, double step_store_1, double *p, double *time, double (*f) (double, double)) {
	double t = 0., k_1, k_2, a = 1e-3;
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
