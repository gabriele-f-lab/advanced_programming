#include <stdio.h>

int main(){
	float temp_C;
	float temp_F;

	printf("Temperatura in Fahreneit= \n");
	scanf("%f", &temp_F);
	temp_C = (temp_F - 32.0) / 1.8; 

	printf("Temperatura in Celsius= %f\n", temp_C);


}
