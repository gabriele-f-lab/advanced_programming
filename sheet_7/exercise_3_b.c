#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
    FILE *fp;
    char a;
    int contr = 1, cont, n_words = 0;
    
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
        cont = 0;
        do {
            contr = fscanf(fp, "%c", &a);
            cont = 1;
        } while (contr == 1 && !isblank(a) && a != '\n');
        do {
            contr = fscanf(fp, "%c", &a);
        } while (contr == 1 && (isblank(a) || a == '\n'));
        n_words += cont;
    } while (contr == 1);

    printf("Number of words: %d\n", n_words);

    fclose(fp);

    return 0;
}
