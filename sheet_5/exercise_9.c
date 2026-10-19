#include <stdio.h>
#include <math.h>

#define PI 4.*atan(1.0)

struct polygon {
	int n_sides;
	double side_length;
};

struct polygon createPolygon(void);
double calculateArea(struct polygon p);
double peripoli(struct polygon p);
void doubleperi(struct polygon *pp);

int main() {
	struct polygon pol;	

	pol = createPolygon();
	printf("The area of the polygon is %f \n", calculateArea(pol));
	printf("The perimeter of the polygon is %f \n", peripoli(pol));

	doubleperi(&pol);
	//check new area and perimeter
	printf("The area of the polygon is %f \n", calculateArea(pol));
	printf("The perimeter of the polygon is %f \n", peripoli(pol));
}

struct polygon createPolygon(void){
	int n;
	float l;
	struct polygon pol;

	printf("Insert the number of sides ");
	scanf("%d", &n);
	printf("Insert the side length ");
	scanf("%f", &l);

	pol.n_sides = n;
	pol.side_length = l;

	return pol;
}

double calculateArea(struct polygon p){
	return p.n_sides * pow(p.side_length, 2.) / (4. * tan (PI / p.n_sides));
}

double peripoli(struct polygon p){
	return p.n_sides * p.side_length;
}

void doubleperi(struct polygon *pp){
	(*pp).side_length = (*pp).side_length * 2.;
}
