#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 10000 /* size of available space */
#define maxblock 100

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */
char *lineptr[MAXLINES]; /* pointers to text lines */
int numeric[maxblock], reverse[maxblock], fold[maxblock], dir[maxblock], nblock[maxblock], totblock = 1;
char del;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getline2(char *line, int max);
void qsort2(void *lineptr[], int left, int right, int (*comp) (void *, void *)); /*here is where a pointer to a function, "(*comp)(void *, void *)" is used */
int strcmp2(char *s, char *t);
char *alloc(int n);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int c; /* 1 if numeric sort */
    int cont = 0, i = 0;

    for (int s = 0; s < maxblock; s++) {
        numeric[s] = reverse[s] = fold[s] = dir[s] = 1;
        nblock[s] = 0;
    }

    if (argc == 3) {
        del = argv[1][0];
        if(argv[1][1]!= '\0') {
            printf("First argument must have only one character\n");
            return 1;
        }
        
        if(argv[2][i] != '-') {
            printf("Second argument must start with a digit\n");
            return 1;
        }
        
        while (argv[2][i] != '\0') {
            if (argv[2][i] == '-') {
                if (i != 0) {
                    totblock++;
                    cont++;
                }
            }
            else {
                switch (argv[2][i]) {
                    case 'r':
                        reverse[cont] = -1;
                        break;
                    case 'n':
                        numeric[cont] = -1;
                        break;
                    case 'f':
                        fold[cont] = -1;
                        break;
                    case 'd':
                        dir[cont] = -1;
                        break;
                    default:
                        printf("find: illegal option %c\n", argv[2][i]);
                        return 1;
                }
            }
            i++;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort2((void **) lineptr, 0, nlines-1, (int (*)(void*, void*))strcmp2); /* here is where the pointer to the correct function is passed */

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

int strcmp2(char *s, char *t) {
    int number = 0;
    double v1, v2;
    int result = 0;
    char c1, c2;

    while (number < totblock) {
        int i = 0, j = 0;

        if (numeric[number] == 1) {
            while (i < ALLOCSIZE && j < ALLOCSIZE) {
                if (dir[number] == -1) {
                    while (!isdigit(s[i]) && !isalpha(s[i]) && s[i] != ' ' && s[i] != '\0' && s[i] != del) i++;
                    while (!isdigit(t[j]) && !isalpha(t[j]) && t[j] != ' ' && t[j] != '\0' && t[j] != del) j++;
                }

                if (fold[number] == 1) {
                    if (s[i] != t[j]) {
                        result = (s[i] - t[j]) * reverse[number];
                        break;
                    } else {
                        if (s[i] == '\0' || s[i] == del) {
                            result = 0;
                            break;
                        }
                    }
                } else {
                    if (tolower(s[i]) != tolower(t[j])) {
                        result = (tolower(s[i]) - tolower(t[j])) * reverse[number];
                        break;
                    } else {
                        if (s[i] == '\0' || s[i] == del) {
                            result = 0;
                            break;
                        }
                    }
                }
                i++;
                j++;
            }

            if (result == 0 && s[i] != t[j]) {
                c1 = (s[i] == del) ? '\0' : s[i];
                c2 = (t[j] == del) ? '\0' : t[j];
                result = (c1 - c2) * reverse[number];
            }

        } else {
            v1 = atof(s);
            v2 = atof(t);
            if (v1 < v2)
                result = -1 * reverse[number];
            else if (v1 > v2)
                result = 1 * reverse[number];
            else
                result = 0;
        }

        if (result != 0) {
            return result;
        }

        while (*s != '\0' && *s != del) {
            s++;
        }

        if (*s == del) {
            s++;
        }

        while (*t != '\0' && *t != del) {
            t++;
        }
        if (*t == del) {
            t++;
        }

        number++;
    }

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
