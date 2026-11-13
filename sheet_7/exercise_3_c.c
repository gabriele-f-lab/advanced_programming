#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
    FILE *fp;
    char a;
    int contr = 1, n_lines = -1;
    
    if (argc < 2) {
        printf("Insert the input file name\n");

        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Invalid file name\n");

        return 1;
    }

    do {
        contr = fscanf(fp, "%c", &a);
        if (a == '\n')
            n_lines++;
    } while (contr == 1);

    printf("Number of lines: %d\n", n_lines);

    fclose(fp);

    return 0;
}
