#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POSSIBLE_GREYS_THRESHOLDS 256
#define FILE_ERR 1

typedef struct dimension {
	int height;
	int width;
} dimensions;


typedef struct clusters {
	int flag;
	int np;
	double mean;
	double std_dev;
	int* next;
} cluster;

int read_data(FILE* fp, int** arr, dimensions d)
{
	clock_t t;
	double time_taken;
	int i, j;

	t = clock();
	for (i = 0; i < d.height; i++)
		for (j = 0; j < d.width; j++)
			fscanf(fp, "%d", &arr[i][j]);

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Data read in %lf ms\n", time_taken);
	return 0;
}

int* frequency(FILE* fp, int** arr, dimensions d)
{
	int i, j, k;
	int* frequency = (int*)malloc(sizeof(int*) * 256);

	for (i = 0; i < POSSIBLE_GREYS_THRESHOLDS; i++) {
		for (j = 0; j < d.height; j++)
			for (k = 0; k < d.height; k++)
				frequency[arr[j][k]] = arr[j][k];
	}
	return frequency;
}


int threshold(FILE* fp, int** arr, dimensions d, cluster* A, cluster* B)
{
	clock_t t;
	t = clock();
	FILE* res = fopen("result.dat", "w");
	fprintf(res, "#th d' np\n");
	int* freq = frequency(fp, arr, d);
	int i, j;

	double time_taken;

	for (i = 1; i < POSSIBLE_GREYS_THRESHOLDS; i++) {
		int low_sum = 0;
		int up_sum = 0;
		int npa = 0;
		int npb = 0;
		int sum_std_dev;
		for (j = 0; j < i; j++) {
			low_sum += freq[j];
			//if (freq[i] != 0)
				npa++;
		}
		for (j = i; j < POSSIBLE_GREYS_THRESHOLDS; j++) {
			up_sum += freq[j];
			//if (freq[i] != 0)
				npb++;
		}

		A->np = npa;
		A->mean = (double)low_sum / A->np;
		for (j = 0; j < i; j++)
			sum_std_dev = sum_std_dev + pow((freq[j] - A->mean), 2);
		A->std_dev = sqrt(sum_std_dev / (double)A->np);

		sum_std_dev = 0;

		B->np = npb;
		B->mean = (double)up_sum / B->np;
		for (j = i; j < POSSIBLE_GREYS_THRESHOLDS; j++)
			sum_std_dev = sum_std_dev + pow((freq[j] - B->mean), 2);
		B->std_dev = sqrt(sum_std_dev / (double)B->np);

		double n_ratio = (double)A->np / (double)B->np;
		double di = fabs(A->mean - B->mean)
			    / sqrt(pow(A->std_dev, 2) + pow(B->std_dev, 2));
		fprintf(res, "%d %lf %lf\n", i, di, n_ratio);
	}

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Iterative thresholding done in %lf ms\n", time_taken);

	return 0;
}

int main(int argc, char* argv[])
{
	FILE* fp = fopen(argv[1], "r");

	if (fp == NULL) {
		printf("File cannot be opened or does not exist.\n");
		return FILE_ERR;
	}

	dimensions d;
	fscanf(fp, "%d %d", &d.height, &d.width);

	int i;
	//allocating a 2d array
	int **arr = (int**)malloc(d.height * sizeof(int**));
	for (i = 0; i < d.height; i++)
		arr[i] = (int*)malloc(d.width * sizeof(int*));

	//Reading data
	read_data(fp, arr, d);
	cluster A, B;
	//Thresholding data
	threshold(fp, arr, d, &A, &B);
	//Freeing memory
	for (i = 0; i < d.height; i++)
		free(arr[i]);
	free(arr);
	return 0;
}
