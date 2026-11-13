#include <stdio.h>

#define maxch 1000000

void uncomment(void);

int main() {
    uncomment();

    return 0;
}

void uncomment (void) {
    int c, next, old, cont, cont_row, br_cont;

    c = getchar();
    next = getchar();
    ungetc(next, stdin);

    while (c!= EOF) {
        while (c != EOF && (c != '/' && next != '/') && (c != '/' && next != '*') && c != '\'' && c != '"') {
            putchar(c);
            old = c;
            c = getchar();
            next = getchar();
            ungetc(next, stdin);
        }
        if (c == EOF)
            break;
        switch (c) {
            case '\'':
                putchar(c);
                old = c;
                c = getchar();
                next = getchar();
                ungetc(next, stdin);
                while (c != EOF) {
                    if(c == '\'' && old != '\\')
                        break;
                    putchar(c);
                    old = c;
                    c = getchar();
                    next = getchar();
                    ungetc(next, stdin);
                }
                putchar(c);
                old = c;
                c = getchar();
                next = getchar();
                ungetc(next, stdin);
                break;
            case '"':
                br_cont = 0;
                putchar(c);
                old = c;
                c = getchar();
                next = getchar();
                ungetc(next, stdin);
                while (c != EOF) {
                    if(c == '"' && br_cont%2 == 0)
                        break;
                    if(c == '\\') 
                        br_cont++;
                    else
                        br_cont = 0;
                    putchar(c);
                    old = c;
                    c = getchar();
                    next = getchar();
                    ungetc(next, stdin);
                }
                putchar(c);
                old = c;
                c = getchar();
                next = getchar();
                ungetc(next, stdin);
                break;
            default:
                if (c == '/' && next == '/') {
                    cont = 0;
                    while (c != EOF) {
                        if (c == '\n') {
                            putchar(c);
                            old = c;
                            c = getchar();
                            next = getchar();
                            ungetc(next, stdin);
                            break;
                        }
                        old = c;
                        c = getchar();
                        next = getchar();
                        ungetc(next, stdin);
                    }
                }
                else if (c == '/' && next == '*') {
                    cont = 0;
                    cont_row = 0;
                    while (c != EOF) {
                        if (old == '\n')
                            cont = 2;
                        if (c == '\n')
                            cont_row++;
                        if (c == '*' && next == '/') {
                            old = c;
                            c = getchar();
                            next = getchar();
                            ungetc(next, stdin);
                            old = c;
                            c = getchar();
                            next = getchar();
                            ungetc(next, stdin);
                            if (c == '\n' && cont_row != 0) {
                                old = c;
                                c = getchar();
                                next = getchar();
                                ungetc(next, stdin);
                            }
                            break;
                        }
                        if (c == '\n') {
                            cont++;
                            if (cont <= 1)
                                putchar(c);
                        }
                        old = c;
                        c = getchar();
                        next = getchar();
                        ungetc(next, stdin);
                    }
                } else {
                    putchar(c);
                    old = c;
                    c = getchar();
                    next = getchar();
                    ungetc(next, stdin);
                }
                break;
        }
    }
}
