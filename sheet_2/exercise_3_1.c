#include <stdio.h>

int main(){
	float temp_C;
	float temp_F;

	printf("Temperatura in Celsius= \n");
	scanf("%f", &temp_C);
	temp_F = temp_C * 1.8 + 32.;

	printf("Temperatura in Fahreneit= %f\n", temp_F);


}
