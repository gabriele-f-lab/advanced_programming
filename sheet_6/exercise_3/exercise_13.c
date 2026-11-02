#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLEN 1000 /* max length of any input line */
#define maxnum 100

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int n_output);
int getline2(char *, int);
char *alloc2(int);

int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int n = 10, i;
    char number[maxnum];

    if (argc > 3) {
        printf("Too many arguments\n");
        return 0;
    } else {
        if (argc == 2) {
            if (argv[1][0] == '-') {
                for (i = 1; argv[1][i] != '\0'; i++){
                    if (!isdigit(argv[1][i])) {
                        printf("Wrong argument passed\n");
                        return 0;
                    }
                }
                for (int j = 0; j < i - 1; j++) number[j] = argv[1][j+1];
                number[i-1] = '\0';
                n = atoi(number);
            } else {
                printf("Wrong argument passed\n");
                return 0;
            }
        }
        if (argc == 3) {
            if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0') {
                for (i = 0; argv[2][i] != '\0'; i++){
                    if (!isdigit(argv[2][i])) {
                        printf("Wrong argument passed\n");
                        return 0;
                    }
                }
                n = atoi(argv[2]);
            } else {
                printf("Wrong argument passed\n");
                return 0;
            }
        }
    }
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        writelines(lineptr, nlines, n);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline2(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc2(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int n_output) {
    int i, i_min;

    i_min = nlines - n_output < 0 ? 0 : nlines - n_output;
    for (i = i_min; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline2: read a line into s, return length */
int getline2(char s[],int lim) {
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

char *alloc2(int n) /* return pointer to n characters */ {
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough room */
        return 0;
}
