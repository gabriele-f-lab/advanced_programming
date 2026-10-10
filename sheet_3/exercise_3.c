#include <stdio.h>
#include <math.h>

int main() {
	
	double a, b, c, d, x_1, x_2;

	printf("Considering the following notation: a x^2 + b x + c = 0 \n");
	printf("provide the \"a\" coefficient \n");
	scanf("%lf", &a);
	printf("provide the \"b\" coefficient \n");
	scanf("%lf", &b);
	printf("provide the \"c\" coefficient \n");
	scanf("%lf", &c);

	if (a == 0) {
		x_1 = -c / b;

		printf("The root is %lf \n", x_1);

	} else {
		d = pow(b, 2.) - 4.*a*c;
		if (d < 0) {
			printf("There are no real roots\n");
		} else {
			x_1 = d == 0 ? -b/(2.*a) : (-b - sqrt(d))/(2.*a);
			x_2 = d == 0 ? -b/(2.*a) : (-b + sqrt(d))/(2.*a);

			printf("The roots are x_1=%lf and x_2=%lf\n", x_1, x_2);
		}
	}

}
