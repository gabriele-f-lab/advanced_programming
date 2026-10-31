#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_max 100


void strcpy2(char *s, char *t, int n);
void strcat2(char *s, char *t, int n);
void strcmp2(char *s, char *t, int n);

int main() {
    int res, n_lim = 3;
    char *string_1 = (char *) malloc(n_max * sizeof(char));
    char *string_2 = (char *) malloc(n_max * sizeof(char));

    string_1 = strcpy(string_1, "1234567891");
    string_2 = strcpy(string_2, "abcdefghij");
    
    strcpy2(string_1, string_2, n_lim);
    printf("strcpy result: %s\n", string_1);
    
    strcat2(string_1, string_2, n_lim);
    printf("strcat result: %s\n", string_1);

    free(string_1);
    free(string_2);
    return 0;
}


void strcpy2(char *s, char *t, int n) {
int i, j, equiv = 1;
    i=j=0;
    while (s[i] != '\0')
        i++;
    while (t[i] != '\0' && j < n) {
        s[i+j] = t[j];
        j++;
    }
}

void strcat2(char *s, char *t, int n) {
}

void strcmp2(char *s, char *t, int n) {
}
