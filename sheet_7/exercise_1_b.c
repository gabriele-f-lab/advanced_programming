#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define max_val 10000000

int main (int argc, char **argv) {
    int a, b, cont = 0;
    FILE *ins_circle, *out_circle;
    srand(time(0));

    if (argc < 2) {
        printf("Insert the number of points\n");

        return 1;
    }

    ins_circle = fopen("ins_circle.txt", "w");
    out_circle = fopen("out_circle.txt", "w");
    for (int i = 0; i < atoi(argv[1]); i++) {
        a = rand() % max_val;
        b = rand() % max_val;

        if (pow((float) a - (float) max_val / 2., 2.) + pow((float) b - (float) max_val / 2., 2.) <= pow((float) max_val / 2., 2.)) {
            fprintf(ins_circle, "%d, %d\n", a, b);
            cont++;
        }
        else {
            fprintf(out_circle, "%d, %d\n", a, b);
        }
    }

    printf("Computed value of greek pi: %f\n", 4.*(float) cont / atof(argv[1]));

    fclose(ins_circle);
    fclose(out_circle);

    return 0;
}
