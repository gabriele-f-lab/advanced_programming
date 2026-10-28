#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int);
int getint(int *pn);

int main () {
	int n, array[SIZE], a;
	for (n = 0; n < SIZE; n++) {
		a = getint(&array[n]);
		if (a == 0) {
			getch();
			n--;
			continue;
		}
		if (a == EOF) break;
	}

	for (int j = 0; j < n; j++) {
		printf("%d\n", array[j]);
	}

	return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
    {
        int c, sign, temp;
        while (isspace(c = getch())) /* skip white space */
            ;
        if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
        {
            ungetch(c);  /* it's not a number */
            return 0;
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-' ) {
	    temp = c;
            c = getch();
	    if (!isdigit(c)) {
		    if (c != EOF) ungetch (c);
		    ungetch (temp);
		    return 0;
	    }
	}

        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
        *pn *= sign;

        if (c != EOF)
            ungetch (c) ;

        return c;
}

int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
