// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 6

#include "b.h"

int** maker(int n, int m)
{
	int i, j;
	int **arr = malloc(n * sizeof(int*));

	for (i = 0; i < n; i++)
		arr[i] = (int*)malloc(m * sizeof(int));

	srand(time(NULL));      // Seed

	for (i = 0; i <  n; i++)
		for (j = 0; j < m; j++)
			arr[i][j] = rand();
	return arr;
}

void writer(int** matrix, int n, int m, char* filename)
{
	FILE* fp = fopen(filename, "w");

	if (fp == NULL) {
		printf("File %s cannot be opened or does not exist\n", filename);
		return;
	}

	int i, j;
	for (i = 0; i <  n; i++) {
		for (j = 0; j < m; j++)
			fprintf(fp, "%d ", matrix[i][j]);
		fprintf(fp, "\n");
	}
}

void printDelete(int** matrix, int n, int m)
{
	int i, j;

	for (i = 0; i <  n; i++) {
		for (j = 0; j < m; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}

	for (i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}
