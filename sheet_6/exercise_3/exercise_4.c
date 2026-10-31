#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_max 100


int strend(char *s, char *t);

int main(int argc, char *argv[]) {
    int res;
    char *string_1 = (char *) malloc(n_max * sizeof(char));
    char *string_2 = (char *) malloc(n_max * sizeof(char));

    if (argc < 3) {
        printf("Arguments missing: insert 2 strings\n");
        return 0;
    }

    string_1 = strcpy(string_1, argv[1]);
    string_2 = strcpy(string_2, argv[2]);
    
    res = strend(string_1, string_2);
    if (res != 10) printf("Result: %d\n", res);
    else printf("string 2 must be shorter or equal in length to string 1\n");

    free(string_2);
    free(string_1);
    return 0;
}


int strend(char *s, char *t) {
int i, j, equiv = 1;
    i=j=0;
    while (s[i]!='\0')
        i++;
    while (t[j]!='\0')
        j++;
    if (j > i) return 10;
     
    for (int cont = i - j; cont < i; cont++) {
        if (s[cont] != t[cont - (i - j)]) equiv = 0; 
    }

    return equiv;
}

