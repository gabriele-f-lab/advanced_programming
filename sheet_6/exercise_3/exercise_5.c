#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_max 100


void strncpy2(char *s, char *t, int n);
void strncat2(char *s, char *t, int n);
int strncmp2(char *s, char *t, int n);

int main(int argc, char *argv[]) {
    int res, n_lim;
    char *string_1, *string_2, *original;

    if (argc < 4) {
        printf("Arguments missing: insert 2 strings and n\n");
        return 0;
    }

    n_lim = atoi(argv[3]);
    string_1 = (char *) malloc(n_max * sizeof(char));
    string_2 = (char *) malloc(n_max * sizeof(char));
    original = (char *) malloc(n_max * sizeof(char));

    string_1 = strcpy(string_1, argv[1]);
    string_2 = strcpy(string_2, argv[2]);
    original = strcpy(original, string_1);

    strncpy2(string_1, string_2, n_lim);
    printf("strncpy2 result: %s\n", string_1);
    
    string_1 = strcpy(string_1, original);
    strncat2(string_1, string_2, n_lim);
    printf("strncat2 result: %s\n", string_1);

    string_1 = strcpy(string_1, original);
    res = strncmp2(string_1, string_2, n_lim);
    printf("strncmp2 result: %d\n", res);

    free(original);
    free(string_2);
    free(string_1);
    return 0;
}


void strncpy2(char *s, char *t, int n) {
    int i = 0;

    while (t[i] != '\0' && i < n) {
        s[i] = t[i];
        i++;
    }
    s[i] = '\0';
}

void strncat2(char *s, char *t, int n) {
    int i = 0, j = 0;

    while (s[i] != '\0')
        i++;
    while (t[j] != '\0' && j < n) {
        s[i+j] = t[j];
        j++;
    }
    s[i+j] = '\0';
}

int strncmp2(char *s, char *t, int n) {
    int i = 0;

    while (i < n && s[i] == t[i]) {
        if (s[i] == '\0') return 0;
        if (i + 1 == n) break;
        i++;
    }
    return s[i] - t[i];
}
