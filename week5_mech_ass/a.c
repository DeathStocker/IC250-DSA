#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define FILE_ERR 1

/*
   Prints calloc() error message.
 */
int err_calloc()
{
	printf("Error allocating memory.\nExitting.\n");
	return FILE_ERR;
}

/*
   Creates a matrix.
 */
double** create_matrix(int n, int m)
{
	int i;
	double **arr = calloc(n, sizeof(double*));

	if (arr == NULL)
		return NULL;

	for (i = 0; i < n; i++) {
		arr[i] = calloc(m, sizeof(double));
		if (arr[i] == NULL)
			return NULL;
	}

	return arr;
}

void free_matrix(double** arr, int n, int m)
{
	int i;

	(void)m;        // To suppress the warnings.

	if (arr == NULL)
		printf("Cannot free pointer pointing to NULL.\n");

	for (i = 0; i < n; i++)
		free(arr[i]);

	free(arr);
}

/*
   Creates an Augmented matrix from a matrix and a result vector.
 */
double** create_aug_matrix(double** mat, double* arr, int m, int n)
{
	double** aug = create_matrix(m, n);

	if (aug == NULL)
		return NULL;

	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n - 1; j++)
			aug[i][j] = mat[i][j];
	for (i = 0; i < m; i++)
		aug[i][n - 1] = arr[i];

	return aug;
}

/*
   Checks if the matrix is tridiagonal or not.
 */
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

/*
   Initializes the matrix with the given values.
 */
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

/*
   Performs Gauss elimination on the given Augmented matrix.
 */
double* gauss_eliminate(double** aug, int n)
{
	int i, j, k;
	double c, sum = 0.0;

	double* res = calloc(n, sizeof(double));

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

/*
   Prints the matrix.
 */
void display_matrix(double** arr, int m, int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%lf\t", arr[i][j]);
		printf("\n");
	}
}

/*
   Prints the vector.
 */
void display_array(double* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%lf\t", arr[i]);
	printf("\n");
}

/*
   Calculates the analytical theta_exact for the given problem.
 */
double* calc_theta_exact(double delta_x, double beta, int N)
{
	int i;
	double* theta_exact = calloc(N, sizeof(double));

	double count;

	for (i = 0, count = 0.0; i < N; i++, count += delta_x)
		theta_exact[i] = cosh(sqrt(beta) * (1 - count)) / cosh(sqrt(beta));

	return theta_exact;
}

/*
   Prints the data to a file "results.dat"
 */
int print_to_file(int ch, double* theta, double* theta_exact, int N, double delta_x)
{
	int i;
	double count = 0.0;
	char str[16] = "results";

	strcat(str, (ch == 0) ? "_gauss" : "_thomas");
	strcat(str, ".dat");

	FILE* fp = fopen(str, "w");

	if (fp == NULL) {
		printf("Cannot open file for writing. Exitting.\n");
		return FILE_ERR;
	}
	fprintf(fp, "#delta_x  theta_%s   theta_exact\n\n", (ch == 0) ? "_gauss" : "_thomas");

	for (i = 0; i < N; i++, count += delta_x)
		fprintf(fp, "%lf %lf %lf\n", count, theta[i], theta_exact[i]);

	fclose(fp);

	return 0;
}

/*
   Calculates the amount of memory allocated in the heap.
 */
void calc_size_heap(double* a, double* b, double* d, double** mat, double** aug,
		    double* r, double* res, double* theta_exact, int N)
{
	double space = sizeof(a) * (N - 1) + sizeof(b) * (N - 1) + sizeof(d) * N
		       + sizeof(mat) * (N * N) + sizeof(aug) * (N * (N + 1))
		       + sizeof(res) * N + sizeof(r) * N + sizeof(theta_exact) * N;

	printf("Space used = %.3lf KB\n", space / 1000);
}

double calc_theta_error(double* theta, double* theta_exact, int N)
{
	double theta_error = 0.0;
	int i;

	for (i = 0; i < N; i++)
		theta_error = pow(theta_exact[i] - theta[i], 2);
	theta_error /= N;
	theta_error = sqrt(theta_error);
	return theta_error;
}

double* calc_theta_Thomas(double* a, double* b, double* d, double* r, int N)
{
	int i;

	for (i = 1; i < N; i++) {
		d[i] -= (a[i - 1] * b[i - 1] / d[i - 1]);
		r[i] -= (r[i - 1] * b[i - 1] / d[i - 1]);
	}

	double* theta = calloc(N, sizeof(double));
	theta[N - 1] = r[N - 1] / d[N - 1];

	for (i = N - 2; i > 0; i--)
		theta[i] = (r[i] - a[i] * theta[i + 1]) / d[i];
	theta[0] = 1.0;

	return theta;
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
		return err_calloc();

	double* a = calloc((N - 1), sizeof(double));
	double* b = calloc((N - 1), sizeof(double));
	double* d = calloc(N, sizeof(double));
	double* r = calloc(N, sizeof(double));

	mat = init_matrix(mat, N, delta_x, beta, a, b, d, r);

	if (isTriDiagonal(mat, N))
		printf("Matrix is tridiagonal.\n");

	double** aug = create_aug_matrix(mat, r, N, N + 1);

	double* res = gauss_eliminate(aug, N);

	double* theta_exact = calc_theta_exact(delta_x, beta, N);

	print_to_file(0, res, theta_exact, N, delta_x);

	calc_size_heap(a, b, d, mat, aug, r, res, theta_exact, N);

	double error = calc_theta_error(res, theta_exact, N);
	printf("Error(theta, theta_exact) = %lf\n", error);

	double* theta_thomas = calc_theta_Thomas(a, b, d, r, N);
	print_to_file(1, theta_thomas, theta_exact, N, delta_x);

	// Freeing all the pointers.
	free(res);
	free(theta_exact);
	free_matrix(mat, N, N);
	free(a);
	free(b);
	free(d);
	free(r);
	free_matrix(aug, N, N + 1);
	free(theta_thomas);

	return 0;
}
