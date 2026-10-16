#include <stdio.h>
#include <stdlib.h>


int main(){
	int **M, **MT;
	int n, m, i, j, cont = 0;

	printf("Insert the number of rows\n");
	scanf("%d", &n);
	printf("Insert the number of columns\n");
	scanf("%d", &m);

	M = (int**)malloc(n*sizeof(int*));

	for (i = 0; i < n; i++)
	M[i] = (int*)malloc(m*sizeof(int));
	
	MT = (int**)malloc(m*sizeof(int*));

	for (i = 0; i < m; i++)
	MT[i] = (int*)malloc(n*sizeof(int));

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("Insert %d, %d entry\n", i, j);
			scanf("%d", &M[i][j]);
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			MT[i][j] = M[j][i];
		}
	}

	printf("M:\n");	
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
	
	printf("MT:\n");	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", MT[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < n; i++) free(M[i]);
	free(M);
}
