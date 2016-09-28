#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define clear() printf("\033[H\033[J")

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
void calc_size_heap(int ch, double* a, double* b, double* d, double** mat,
		    double** aug, double* r, double* res, double* theta_exact,
		    double* theta_thomas, int N)
{
	double space;

	switch (ch) {
	case 0:
		space = sizeof(mat) * (N * N) + sizeof(aug) * (N * (N + 1))
			+ sizeof(res) * N + sizeof(theta_exact) * N + sizeof(r) * N;
		break;
	case 1:
		space = sizeof(a) * (N - 1) + sizeof(b) * (N - 1) + sizeof(d) * N
			+ sizeof(mat) * (N * N) + sizeof(r) * N
			+ sizeof(theta_exact) * N + sizeof(theta_thomas) * N;
	}

	printf("Space used in %s = %.3lf KB\n", (ch == 0) ? "Gauss" : "Thomas",
	       space / 1000);
}

double calc_theta_error(double* theta, double* theta_exact, int N)
{
	double theta_error = 0.0;
	int i;

	for (i = 0; i < N; i++)
		theta_error += pow(theta_exact[i] - theta[i], 2);
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

	// display_array(r, N);
	// display_array(d, N);

	for (i = N - 2; i >= 0; i--)
		theta[i] = (r[i] - a[i] * theta[i + 1]) / d[i];

	return theta;
}

/*
   To plot the obtained data and output them to image files
 */
int plot()
{
	/*
	   Commands for gnuplot
	 */
	char* plottingA[] = { "set terminal png",
			      "set title \"Gauss\"",
			      "set output 'gauss.png'",
			      "plot 'results_gauss.dat' using 1:2 title 'Theta_calc' with line, 'results_gauss.dat' using 1:3 title 'Theta_exact' with line linecolor rgb 'black'" };

	char* plottingB[] = { "set terminal png",
			      "set title \"Thomas\"",
			      "set output 'thomas.png'",
			      "plot 'results_thomas.dat' using 1:2 title 'Theta_calc' with line, 'results_thomas.dat' using 1:3 title 'Theta_exact' with line linecolor rgb 'black'" };
	char* plottingC[] = { "set terminal png",
			      "set title \"Gauss\"",
			      "set output 'gauss_error.png'",
			      "plot 'NvsErr_Gauss.dat' using 1:2 title 'Error' with line" };
	char* plottingD[] = { "set terminal png",
			      "set title \"Thomas\"",
			      "set output 'thomas_error.png'",
			      "plot 'NvsErr_Thomas.dat' using 1:2 title 'Error' with line" };

	int i;
	FILE* gnuplotPipe = popen("gnuplot -persistent", "w");

	/*
	   Piping outputs to GNUPlot for saving the different graphs in
	   portable network graphics files.
	 */
	for (i = 0; i < 4; i++)
		fprintf(gnuplotPipe, "%s \n", plottingA[i]);
	for (i = 0; i < 4; i++)
		fprintf(gnuplotPipe, "%s \n", plottingB[i]);
	for (i = 0; i < 4; i++)
		fprintf(gnuplotPipe, "%s \n", plottingC[i]);
	for (i = 0; i < 4; i++)
		fprintf(gnuplotPipe, "%s \n", plottingD[i]);
	pclose(gnuplotPipe);
	return 0;
}

int main()
{
	printf("Enter the value of N = ");
	int N;
	scanf("%d", &N);
	if (N <= 1) {
		printf("Value of N is cannot be less than or equal to 1.\n");
		return err_calloc();
	}
	double beta;
	printf("Enter the value of beta (Fixed) = ");
	scanf("%lf", &beta);

	// Clears the screen.
	clear();

	double delta_x = 1.0 / (N - 1);

	// Allocating space for the matrix
	double **mat = create_matrix(N, N);
	if (mat == NULL)
		return err_calloc();

	double* a = calloc((N - 1), sizeof(double));
	double* b = calloc((N - 1), sizeof(double));
	double* d = calloc(N, sizeof(double));
	double* r = calloc(N, sizeof(double));
	if (a == NULL || b == NULL || d == NULL || r == NULL)
		return err_calloc();

	// Initializes the matrix A.
	mat = init_matrix(mat, N, delta_x, beta, a, b, d, r);

	if (isTriDiagonal(mat, N))
		printf("Matrix is tridiagonal.\n");

	printf("\n\n");

	clock_t t;
	t = clock();
	// Creates an augmented matrix from matrix A and vector V.
	double** aug = create_aug_matrix(mat, r, N, N + 1);

	// Performs Gauss elimination and returns the resultant vector.
	double* res = gauss_eliminate(aug, N);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Time taken in Gauss = %lfms\n", time_taken);

	// Calculates the exact value of theta.
	double* theta_exact = calc_theta_exact(delta_x, beta, N);

	// Prints to file results_gauss.dat.
	print_to_file(0, res, theta_exact, N, delta_x);

	// Calculates the size allocated in the heap for Gauss method.
	calc_size_heap(0, a, b, d, mat, aug, r, res, theta_exact, NULL, N);

	// Displays the error of the
	double error_gauss = calc_theta_error(res, theta_exact, N);
	printf("Error(theta, theta_exact) in Gauss = %lf\n", error_gauss);

	printf("\n\n");

	t = clock();
	// Calculates and prints to file using Thomas algorithm.
	double* theta_thomas = calc_theta_Thomas(a, b, d, r, N);

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Time taken in Thomas = %lfms\n", time_taken);

	print_to_file(1, theta_thomas, theta_exact, N, delta_x);

	// Calculates the size allocated in the heap for Thomas method.
	calc_size_heap(1, a, b, d, NULL, NULL, r, NULL, theta_exact, theta_thomas, N);

	// Displays the error of the
	double error_thomas = calc_theta_error(theta_thomas, theta_exact, N);
	printf("Error(theta, theta_exact) in Thomas = %lf\n", error_thomas);

	// Prints the N vs Error table.
	FILE* fp1 = fopen("NvsErr_Gauss.dat", "a");
	fprintf(fp1, "%d\t%lf\n", N, error_gauss);
	FILE* fp2 = fopen("NvsErr_Thomas.dat", "a");
	fprintf(fp2, "%d\t%lf\n", N, error_thomas);

	// Plots the graphs between x* and theta.
	plot();

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
	fclose(fp1);
	fclose(fp2);

	return 0;
}
