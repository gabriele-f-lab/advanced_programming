#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 5000   /* max lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int maxlines, char *p);
void writelines(char *lineptr[], int nlines);
void qsort2(char *lineptr[], int left, int right);
void swap(char *v[], int i, int j);
int getline2(char *, int);

/* sort input lines */
int main()
    {
        int nlines; /* number of input lines read */
        char *store = (char *) malloc (MAXLEN * MAXLINES);

        if ((nlines = readlines(lineptr, MAXLINES, store)) >= 0)

        {
            qsort2(lineptr, 0, nlines-1);
            writelines(lineptr, nlines);
            return 0;
        } 
        else 
        {
            printf("error: input too big to sort\n");
            return 1;

        }
    }

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *p)
    {
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while((len = getline2(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else 
        {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;    /* ...and HERE is where the POINTER to the string is stored in the array */

            p += len;
        }
    
    return nlines;
    }

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
    {
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline: read a line into s, return length */
int getline2(char *s, int lim) {
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

void qsort2(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    
     if (left >= right) /* do nothing if array contains */
        return;         /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0) /* note the strcmp! here is where the double indirection is at work*/
            swap(v, ++last, i);
    swap(v, left, last);
    qsort2(v, left, last-1);
    qsort2(v, last+1, right);
}

/* swap with triviaL changes: */
/* interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
