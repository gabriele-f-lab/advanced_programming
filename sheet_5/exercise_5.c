#include <stdio.h>

int fact_int(int n);
long fact_long(int n);
long long fact_long_long(int n);
float fact_float(int n);
double fact_double(int n);
long double fact_long_double(int n);
void overflow_fact (void);

int main(){
	int m = 0;

	printf("Insert integer number ");
	scanf("%d", &m);

	printf("The factorial of %d is %d \n", m, fact_int(m));
	printf("The factorial of %d is %ld \n", m, fact_long(m));
	printf("The factorial of %d is %lld \n", m, fact_long_long(m));
	printf("The factorial of %d is %f \n", m, fact_float(m));
	printf("The factorial of %d is %lf \n", m, fact_double(m));
	printf("The factorial of %d is %Lf \n", m, fact_long_double(m));

	overflow_fact();
}

int fact_int(int n){
	int val = 1;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

long fact_long(int n){
	long val = 1;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

long long fact_long_long(int n){
	long long val = 1;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

float fact_float(int n){
	float val = 1.;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

double fact_double(int n){
	double val = 1.;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

long double fact_long_double(int n){
	long double val = 1.;

	for (int i = 1; i <= n; i++)
		val = val * i;

	return val;
}

void overflow_fact (void){
	int i = 0;

	do {
		i++;
	} while (fact_int(i+1) / (i+1) == fact_int(i));
	printf("Max with int %d \n", i);
	
	i = 0;
	do {
		i++;
	} while (fact_long(i+1) / (i+1) == fact_long(i));
	printf("Max with long int %d \n", i);
	
	i = 0;
	do {
		i++;
	} while (fact_long_long(i+1) / (i+1) == fact_long_long(i));
	printf("Max with long long int %d \n", i);
	
	i = 0;
	do {
		i++;
	} while (fact_float(i+1) / (i+1) == fact_float(i));
	printf("Max with float %d \n", i);
	
	i = 0;
	do {
		i++;
	} while (fact_double(i+1) / (i+1) == fact_double(i));
	printf("Max with double %d \n", i);
	
	i = 0;
	do {
		i++;
	} while (fact_long_double(i+1) / (i+1) == fact_long_double(i));
	printf("Max with long double %d \n", i);
}
