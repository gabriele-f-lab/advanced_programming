#include <stdio.h>
#include <math.h>

#define PI 4.*atan(1.0)

typedef struct {
	int n_sides;
	double side_length;
} Polygon;

Polygon createPolygon(void);
double calculateArea(Polygon p);
double peripoli(Polygon p);
void doubleperi(Polygon *pp);

int main() {
	Polygon p;	

	p = createPolygon();
	printf("The area of the polygon is %f \n", calculateArea(p));
	printf("The perimeter of the polygon is %f \n", peripoli(p));

	doubleperi(&p);
	//check new area and perimeter
	printf("The area of the polygon is %f \n", calculateArea(p));
	printf("The perimeter of the polygon is %f \n", peripoli(p));
}

Polygon createPolygon(void){
	int n;
	float l;
	Polygon pol;

	printf("Insert the number of sides ");
	scanf("%d", &n);
	printf("Insert the side length ");
	scanf("%f", &l);

	pol.n_sides = n;
	pol.side_length = l;

	return pol;
}

double calculateArea(Polygon p){
	return p.n_sides * pow(p.side_length, 2.) / (4. * tan (PI / p.n_sides));
}

double peripoli(Polygon p){
	return p.n_sides * p.side_length;
}

void doubleperi(Polygon *pp){
	(*pp).side_length = (*pp).side_length * 2.;
}
