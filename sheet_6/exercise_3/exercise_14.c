#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getline2(char *line, int max);
void qsort2(void *lineptr[], int left, int right, int (*comp) (void *, void *)); /*here is where a pointer to a function, "(*comp)(void *, void *)" is used */
void qsort2_r(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
char *alloc(int n);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0, reverse = 0; /* 1 if numeric sort */

    if (argc > 1) {
        switch (argc) {
            case 2:
                if (argv[1][0] == '-' && argv[1][2] == '\0')
                    switch (argv[1][1]) {
                        case 'n':
                            numeric = 1;
                            break;
                        case 'r':
                            reverse = 1;
                            break;
                        default:
                            printf("Wrong argument: insert '-n' or '-r'\n");
                            return 1;
                    }
                else {
                    printf("Wrong argument: insert '-n' or '-r'\n");
                    return 1;
                }
                
                break;

            case 3:
                if((strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "-r") == 0) || ((strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-n") == 0)))
                    numeric = reverse = 1;
                else {
                    printf("Wrong arguments\n");
                    return 1;
                } 

                break;

            default:
                printf("Too many arguments\n");
                return 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (reverse == 0) qsort2((void **) lineptr, 0, nlines-1, (numeric ? (int (*)(void*, void*))numcmp : (int (*)(void*, void*))strcmp)); /* here is where the pointer to the correct function is passed */
        if (reverse == 1) qsort2_r((void **) lineptr, 0, nlines-1, (numeric ? (int (*)(void*, void*))numcmp : (int (*)(void*, void*))strcmp));
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort2: sort v[left] •..v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)   /* here the appropriate function is called. */
            swap(v, ++last, i);           /* so no need to write two DIFFERENT versions of qsort2 */
    swap(v, left, last);
    qsort2(v, left, last-1, comp);
    qsort2(v, last+1, right, comp);
} 

/* qsort2r: sort v[left] •..v[right] into decreasing order */
void qsort2_r(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[left], v[i]) < 0)   /* here the appropriate function is called. */
            swap(v, ++last, i);           /* so no need to write two DIFFERENT versions of qsort2 */
    swap(v, left, last);
    qsort2_r(v, left, last-1, comp);
    qsort2_r(v, last+1, right, comp);
} 

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
        double v1, v2;
        v1 = atof(s1);
        v2 = atof(s2);
        if (v1 < v2)
            return -1;
        else if (v1 > v2)
            return 1;
        else
            return 0;
}

void swap(void * v[], int i, int j) {
        void * temp;
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLINES];

    nlines = 0;
    while((len = getline2(line, MAXLINES)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)  /* note that HERE is where each string is allocated */
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;    /* ...and HERE is where the POINTER to the string is stored in the array */
        }

    return nlines;
}

char *alloc(int n) /* return pointer to n characters */ {
        if (allocbuf + ALLOCSIZE - allocp >= n)  /* it fits */ {
            allocp += n;
            return allocp - n; /* old p */
        }
        else /* not enough room */

        return 0;
}

//getline2: read a line, return length */
int getline2(char *line, int max) {
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}
