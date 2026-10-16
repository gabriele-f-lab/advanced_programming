#include <stdio.h>

struct quadrilater {
	float p_1[2];
	float p_2[2];
	float p_3[2];
	float p_4[2];
};

int main(){
	struct quadrilater q;
	float p1[2], p2[2], p3[3], p4[4], x_mean, y_mean;
	
	//printf("Insert coordinates of point %d separated by a space \n", i);
	scanf("%f %f", &p1[0], &p1[1]);
	scanf("%f %f", &p2[0], &p2[1]);
	scanf("%f %f", &p3[0], &p3[1]);
	scanf("%f %f", &p4[0], &p4[1]);

	x_mean = 0.25 * (p1[0]+p2[0]+p3[0]+p4[0]);
	y_mean = 0.25 * (p1[1]+p2[1]+p3[1]+p4[1]);

	printf("%f, %f", x_mean, y_mean);


}
