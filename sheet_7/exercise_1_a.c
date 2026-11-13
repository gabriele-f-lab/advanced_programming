#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_val 99

int main () {
    int a, b;

    srand(time(0));
    a = rand() % max_val;
    printf("Insert integer number\n");
    do {
        scanf("%d", &b);
        if (b == a)
            printf("Correct\n");
        else {
            if (b > a)
                printf("Too high\n");
            else
                printf("Too low\n");
        }
    } while (b != a);

    return 0;
}
