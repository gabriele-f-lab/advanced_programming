#include <stdio.h>
#include <string.h>


long fibonacci(long n);

int main(){
	long m;
	
	printf("Insert integer number ");

	scanf("%ld", &m);
	printf("%ld\n", fibonacci(m));

	return 0;
}

long fibonacci(long n) {
	/*
	if (n == 1 || n ==2) return 1;
	else return fibonacci(n - 1) + fibonacci(n - 2);
	*/
	long cont = 0;
	int a = 1, b;
	for (int i = 1; i <= n; i++) {
		b = cont;
		cont = cont + a;
		a = b;
	}
	
	return cont;
}
