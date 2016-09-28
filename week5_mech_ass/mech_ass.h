// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 5

#ifndef MECH_ASS
#define MECH_ASS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define clear() printf("\033[H\033[J")

#define FILE_ERR 1

int err_calloc();
double** create_matrix(int n, int m);
void free_matrix(double** arr, int n, int m);
double** create_aug_matrix(double** mat, double* arr, int m, int n);
int isTriDiagonal(double** arr, int N);
double** init_matrix(double** arr, int N, double delta_x, double beta,
		     double* a, double* b, double* d, double* r);
double* gauss_eliminate(double** aug, int n);
void display_matrix(double** arr, int m, int n);
void display_array(double* arr, int size);
double* calc_theta_exact(double delta_x, double beta, int N);
int print_to_file(int ch, double* theta, double* theta_exact, int N, double delta_x);
void calc_size_heap(int ch, double* a, double* b, double* d, double** mat,
		    double** aug, double* r, double* res, double* theta_exact,
		    double* theta_thomas, int N);
double calc_theta_error(double* theta, double* theta_exact, int N);
double* calc_theta_Thomas(double* a, double* b, double* d, double* r, int N);
int plot();

#endif
