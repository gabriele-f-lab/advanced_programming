#include <stdio.h>

int main (int argc, char **argv) {
    FILE *fp;
    char a;
    int contr = 1, cont = 0;
    
    if (argc < 2) {
        printf("Insert the input file name\n");

        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Invalid file name\n");

        return 1;
    }

    while (fscanf(fp, "%c", &a) == 1)
        if (a != '\n')
            cont ++;

    printf("Number of characters: %d\n", cont);

    fclose(fp);

    return 0;
}
