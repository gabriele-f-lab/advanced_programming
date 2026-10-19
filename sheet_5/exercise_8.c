#include <stdio.h>
#include <math.h>

#define points 4
#define PI 4.*atan(1.0)

struct point {
	float x;
	float y;
};

struct point compute_center (struct point q[points]);
float compute_distance (struct point a, struct point b);
float compute_angle (struct point a, struct point b);
void sorting_points (float point_angle[points], int sorted_list[points]);
float compute_perimeter (struct point sorted_q[points]);
float min_distance (struct point q[points]);


int main(){
	struct point quadrilater[points], centroid, sorted_quadrilater[points];
	int sorted_list_main[points];
	float list_angle[points], perimeter;

	for (int i = 0; i < points; i++) {
		printf("Insert x coordinate of point %d\n", i+1);
		scanf("%f", &quadrilater[i].x);
		printf("Insert y coordinate of point %d\n", i+1);
		scanf("%f", &quadrilater[i].y);
	}

	centroid = compute_center(quadrilater);
	printf("%f, %f\n", centroid.x, centroid.y);

	for (int w = 0; w < points; w++){
		list_angle[w] = compute_angle(quadrilater[w], centroid);
	}
	printf("%f\n", list_angle[0]);
	printf("%f\n", list_angle[1]);
	printf("%f\n", list_angle[2]);
	printf("%f\n", list_angle[3]);
	
	sorting_points(list_angle, sorted_list_main);
	printf("%d %d %d %d\n", sorted_list_main[0], sorted_list_main[1], sorted_list_main[2], sorted_list_main[3]);

	for (int p = 0; p < points; p++) {
		sorted_quadrilater[p] = quadrilater[sorted_list_main[p]];
	}

	printf("Perimeter: %f\n", compute_perimeter(sorted_quadrilater));		
	
	printf("Minimum distance: %f\n", min_distance(quadrilater));		
	
	return 0;
}

struct point compute_center (struct point q[points]) {
	struct point center = {0., 0.};

	for (int j = 0; j < points; j++){
		center.x += q[j].x / points;
		center.y += q[j].y / points;
	}	

	return center;
}

float compute_distance (struct point a, struct point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float compute_angle (struct point vert, struct point cent) {
	float ang;
	
	return atan2(vert.y - cent.y, vert.x - cent.x) + PI;
}

void sorting_points (float point_angle[points], int sorted_list[points]) {
	int max;
	float max_val;

	for (int l = 0; l < points; l++){
		max_val = -0.1;
		for (int s = 0; s < points; s++){
			if (point_angle[s] > max_val) {
				max = s;
				max_val = point_angle[s];
			}	
		}
		sorted_list[l] = max;	
		point_angle[max] = -0.1;
	}
}

float compute_perimeter (struct point sorted_q[points]){
	float total = 0.;

	for (int u = 0; u < points; u++) {
		total += compute_distance(sorted_q[u%points], sorted_q[(u+1)%points]);
	}

	return total;
}

float min_distance (struct point q[points]) {
	float min_val = compute_distance(q[0], q[1]);
	
	for (int r = 0; r < points; r++) {
		for (int v = points - 1; v > r; v--) {
			min_val = compute_distance(q[r], q[v]) < min_val ? compute_distance(q[r], q[v]) : min_val;			
		}
	}		
	
	return min_val;
}
