#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
    FILE *fp, *out_file;
    char a;
    
    if (argc < 2) {
        printf("Insert the input file name\n");

        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Invalid file name\n");

        return 1;
    }
    out_file = fopen("output.txt", "w");

    while ((fscanf(fp, "%c", &a)) == 1) {
        a = toupper(a);
        printf("%c", a);
    }

    fclose(fp);
    fclose(out_file);

    return 0;
}
