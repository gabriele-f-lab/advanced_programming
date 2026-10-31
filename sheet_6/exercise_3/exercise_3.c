#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_max 100


void strcat2(char *s, char *t);

int main(int argc, char *argv[]) {
    char *string_1 = (char *) malloc(2 * n_max * sizeof(char));
    char *string_2 = (char *) malloc(n_max * sizeof(char));

    if (argc < 3) {
        printf("Arguments missing: insert 2 strings\n");
        return 0;
    }
    
    string_1 = strcpy(string_1, argv[1]);
    string_2 = strcpy(string_2, argv[2]);

    strcat2(string_1, string_2);

    printf("%s\n", string_1);

    return 0;
}


void strcat2(char *s, char *t) {
    int i, j;
    i=j=0;
    while (s[i]!='\0')
        i++;
    while ((s[i++]=t[j++])!='\0') ; 
}

