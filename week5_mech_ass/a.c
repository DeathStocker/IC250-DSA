#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_ERR 1

/*
   Contains the coordinates of the element.
 */
typedef struct _coordinates {
	int x;
	int y;
} coordinates;

/*
   Contains the position as well as the value of the element.
 */
typedef struct _tuple {
	coordinates pos;
	int val;
} tuple;

int err_malloc()
{
	printf("Error allocating memory.\nExitting.\n");
	return FILE_ERR;
}

double** create_matrix(int n, int m)
{
	int i;
	double **arr = malloc(n * sizeof(double*));

	if (arr == NULL)
		return NULL;

	for (i = 0; i < n; i++) {
		arr[i] = malloc(m * sizeof(double));
		if (arr[i] == NULL)
			return NULL;
	}

	return arr;
}

double** create_aug_matrix(double** mat, double* arr, int m, int n)
{
	double** aug = create_matrix(m, n + 1);

	if (aug == NULL)
		return NULL;

	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			aug[i][j] = mat[i][j];
	for (i = 0; i < m; i++)
		aug[i][n - 1] = arr[i];

	return aug;
}

int isTriDiagonal(double** arr, int N)
{
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = i + 2; j < N; j++)
			if (arr[i][j] != 0)
				return 1;
	}

	for (i = 2; i < N; i++) {
		for (j = 0; j < i; j++)
			if (arr[i][j] != 0)
				return 1;
	}

	return 0;
}

double** init_matrix(double** arr, int N, double delta_x, double beta,
		     double* a, double* b, double* d, double* r)
{
	int i, j;

	// Initializing the matrix with zeroes
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			arr[i][j] = 0.0;
	// Initializing the diagonals of the matrix
	for (i = 0; i < N; i++) {
		arr[i][i] = (-2 / pow(delta_x, 2)) - beta;
		d[i] = arr[i][i];
		if (i < N - 1) {
			arr[i + 1][i] = 1 / pow(delta_x, 2);
			b[i] = arr[i + 1][i];
			arr[i][i + 1] = 1 / pow(delta_x, 2);
			a[i] = arr[i][i + 1];
		}
		r[i] = 0;
	}
	arr[0][0] = 1;
	d[0] = 1;
	arr[N - 1][N - 1] = 1;
	d[N - 1] = 1;
	arr[N - 1][N - 2] = -1;
	b[N - 2] = -1;
	arr[0][1] = 0;
	a[0] = 0;
	r[0] = 1;

	return arr;
}

double* gauss_eliminate(double** aug, int n)
{
	int i, j, k;
	double c, sum = 0.0;

	double* res = malloc(n * sizeof(double));

	for (j = 0; j < n; j++) { /* loop for the generation of upper triangular matrix*/
		for (i = 0; i < n; i++) {
			if (i > j) {
				c = aug[i][j] / aug[j][j];
				for (k = 0; k < n + 1; k++)
					aug[i][k] = aug[i][k] - c * aug[j][k];
			}
		}
	}
	res[n - 1] = aug[n - 1][n] / aug[n - 1][n - 1];
	/* this loop is for backward substitution*/
	for (i = n - 2; i >= 0; i--) {
		sum = 0;
		for (j = i; j < n; j++)
			sum = sum + aug[i][j] * res[j];
		res[i] = (aug[i][n] - sum) / aug[i][i];
	}

	return res;
}

void display_matrix(double** arr, int m, int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%lf\t", arr[i][j]);
		printf("\n");
	}
}

void display_array(double* arr, int size)
{
	int i;

	for(i = 0; i < size; i++) {
		printf("%lf\t", arr[i]);
	}
	printf("\n");
}

int main()
{
	printf("Enter the value of N = ");
	int N;
	scanf("%d", &N);
	double beta = 100.0;
	printf("Enter the value of beta (Fixed) = %d\n", (int)beta);

	double delta_x = 1.0 / (N - 1);

	// Allocating space for the matrix
	double **mat = create_matrix(N, N);
	if (mat == NULL)
		return err_malloc();

	double* a = malloc((N - 1) * sizeof(double));
	double* b = malloc((N - 1) * sizeof(double));
	double* d = malloc(N * sizeof(double));
	double* r = malloc(N * sizeof(double));

	mat = init_matrix(mat, N, delta_x, beta, a, b, d, r);

	if (isTriDiagonal(mat, N))
		printf("Matrix is tridiagonal.\n");

	printf("Matrix = \n");
	display_matrix(mat, N, N);

	double** aug = create_aug_matrix(mat, r, N, N + 1);

	printf("Augmented Matrix = \n");
	display_matrix(aug, N, N + 1);

	double* res = gauss_eliminate(aug, N);

	printf("Results =\n");
	display_array(res, N);

	free(res);
	free(mat);
	free(a);
	free(b);
	free(d);
	free(r);

	return 0;
}
