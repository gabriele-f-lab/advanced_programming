#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define maxdim 100

double store_numbers[maxdim];
int active_numbers;

int new_number(double a);
int operation(char o);

int main (int argc, char *argv[]) {
    int j, cont, control;
    active_numbers = 0;
    
    if (argc == 1) {
        printf("Missing arguments\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        j = 0;

        while(argv[i][j] != '\0') j++;

        if (j == 1) {
            if (isdigit(argv[i][0])) control = new_number(atof(argv[i]));
            else if (argv[i][0] == '+' || argv[i][0] == '-' || argv[i][0] == '*' || argv[i][0] == '/') control = operation(argv[i][0]);
            else {
                printf("Invalid digit: insert a number or an operation symbol\n");            
                return 0;
            }
        }
        else {
            cont = 0;

            if (argv[i][0] != '.' && !isdigit(argv[i][0]) && argv[i][0] != '-' && argv[i][0] != '+') {
                printf("Invalid argument: insert a number or an operation symbol\n");            
                return 0;
            }
            for (int s = 1; s < j; s++) {
                if (isdigit(argv[i][s]) || argv[i][s] == '.') cont += isdigit(argv[i][s]) ? 0 : 1;
                else {
                    printf("Invalid argument: insert a number or an operation symbol\n");            
                    return 0;
                }
            }
            if (cont <= 1) control = new_number(atof(argv[i]));
            else {
                printf("Invalid number: insert only one dot\n");
                return 0;
            }
        }
        if (control == 1) {
            printf("Wrong number of operations\n");
            return 0;
        }
    }

    if (active_numbers == 1) printf("Result: %lf\n", store_numbers[0]);
    else printf("Wrong number of operations\n");

    return 0;
}


int new_number(double a) {
    store_numbers[active_numbers] = a;
    active_numbers++;
    
    return active_numbers > maxdim ? 1 : 0;
}

int operation(char o) {
    if (active_numbers < 2) return 1;

    switch (o) {
        case '+':
            store_numbers[active_numbers-2] += store_numbers[active_numbers-1];
            break;
        case '-':
            store_numbers[active_numbers-2] -= store_numbers[active_numbers-1];
            break;
        case '*':
            store_numbers[active_numbers-2] *= store_numbers[active_numbers-1];
            break;
        case '/':
            store_numbers[active_numbers-2] /= store_numbers[active_numbers-1];
            break;
    }
    active_numbers--;

    return 0;
}
