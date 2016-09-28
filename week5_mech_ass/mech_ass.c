#include "mech_ass.h"

int main(int argc, char* argv[])
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

	// Verbosity for displaying the matrix.
	if (argc == 2 && (strcmp(argv[1], "--verbose") == 0 || strcmp(argv[1], "-v") == 0) )
		display_matrix(mat, N, N);

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
