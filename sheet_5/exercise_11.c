#include <stdio.h>

#define maxch 100000

int uncomment(void);

int main() {
    uncomment();

    return 0;
}

int uncomment (void) {
    char c, text[maxch];
    int i = 0, j = 0, cont, cont_row, ins_str = 0, ins_str2 = 0;

    while ((c = getchar()) && c != EOF) {
        text[i] = c;
        if (i+1 > maxch) {
            printf("File too big\n");
            return 1;
        }
        i++;
    }

    while (j < i && text[j] != EOF) {
        while (j<i-1 && text[j] != EOF && (text[j] != '/' && text[j+1] != '/') && (text[j] != '/' && text[j+1] != '*') && text[j] != '\'' && text[j] != '"') {
            putchar(text[j]);
            j++;
        }
        switch (text[j]) {
            case '\'':
                putchar(text[j]);
                j++;
                while (j<i-1 && text[j] != EOF) {
                    if(text[j] == '\'' && text[j-1] != '\\')
                        break;
                    putchar(text[j]);
                    j++;
                }
                putchar(text[j]);
                j++;
                break;
            case '"':
                putchar(text[j]);
                j++;
                while (j<i-1 && text[j] != EOF) {
                    if(text[j] == '"' && text[j-1] != '\\')
                        break;
                    putchar(text[j]);
                    j++;
                }
                putchar(text[j]);
                j++;
                break;
            default:
                if (text[j] == '/' && text[j+1] == '/') {
                    cont = 0;
                    while (j<i && text[j] != EOF && text[j]) {
                        if (text[j] == '\n') {
                            putchar(text[j]);
                            j++;
                            break;
                        }
                        j++;
                    }
                }
                else if (text[j] == '/' && text[j+1] == '*') {
                    cont = 0;
                    cont_row = 0;
                    ins_str = 0;
                    ins_str2 = 0;
                    while (j<i && text[j] != EOF) {
                        if (text[j-1] == '\n')
                            cont = 2;
                        if (text[j] == '\n')
                            cont_row++;
                        if (text[j] == '\'')
                            ins_str = ins_str == 0 ? 1 : 0;
                        if (text[j] == '"')
                            ins_str2 = ins_str2 == 0 ? 1 : 0;
                        if (text[j] == '*' && text[j+1] == '/' && ins_str == 0 && ins_str2 == 0) {
                            j += 2;
                            if (j<i && text[j] == '\n' && cont_row != 0)
                                j++;
                            break;
                        }
                        if (text[j] == '\n') {
                            cont++;
                            if (cont <= 1)
                                putchar(text[j]);
                        }
                        j++;
                    }
                } else {
                    putchar(text[j]);
                    j++;
                }
                break;
        }
    }
}
