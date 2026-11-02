#include <stdio.h>
#include <stdlib.h>

#define maxdim 100

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, /* note: in C the LAST dimension is the fastest to vary */
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  /* in FORTRAN is the opposite */
} ;

int main (int argc, char *argv[]) {
    int a, b, c, year_day, month, day;
    
    switch (argc) {
        case 3:
            a = atoi(argv[1]);
            b = atoi(argv[2]);
            month_day(a, b, &month, &day);
            if (month < 0 || day < 0) {
                printf("Invalid day of the year\n");
                break;
            }
            printf("The month and the day corresponding to the day of the year %d n° %d, are %d and %d, respectively\n", a, b, month, day);
            
            break;
        case 4:
            a = atoi(argv[1]);
            b = atoi(argv[2]);
            c = atoi(argv[3]);
            year_day = day_of_year(a, b, c);
            if (year_day < 0) {
                printf("Invalid month or day\n");
                break;
            }
            printf("The day of year corresponding to: %d / %d / %d is %d\n", a, b, c, year_day);

            break;
        default:
            printf("Missing (or too many) arguments: insert 2 argument, the year and the day of the year, to obtain the month and the day, or 3 arguments, the year, the month and the day, to obtain the day of the year\n");

            break;
    }

    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month < 0 || month > 12 || day > *(*(daytab + leap) + month)) return -10;
    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + i);
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
        yearday -= *(*(daytab + leap) + i);
        if (i == 12 && yearday > 0) {
            i = -10;
            break;
        }
    }
    *pmonth = i == -10 ? -10 : i;
    *pday = yearday < 0 ? -10 : yearday;
}
