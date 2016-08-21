/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <glib.h>

/*
   Compile using => gcc -o <executable name> <source file.c> -lm -g `pkg-config --cflags --libs glib-2.0`
 */

#define POSSIBLE_GREYS_THRESHOLDS 256
#define FILE_ERR 1

/*
   Dimensions for the image file
 */
typedef struct dimension {
	int height;
	int width;
} dimensions;

/*
   Reads data from the file and stores it in a 2D dynamically allocated array.
 */
int read_data(FILE* fp, int** arr, dimensions d)
{
	clock_t t;
	double time_taken;
	int i, j;

	t = clock();    // Time measurement begins.

	FILE* details = fopen("res.txt", "a");

	for (i = 0; i < d.height; i++)
		for (j = 0; j < d.width; j++)
			fscanf(fp, "%d", &arr[i][j]);

	t = clock() - t;        // Time measurement ends.
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Data read in %lf ms\n", time_taken);
	fprintf(details, "Data read in %lf ms (Iterative method)\n",
		time_taken);

	fclose(details);
	return 0;
}

/*
   Divides the points in the image into two clusters for varying thresholds
   and calculates discriminative index and ratio of number of points for each.
 */
int threshold(int** arr, dimensions d)
{
	clock_t t;
	double time_taken;

	t = clock();    // Time measurement begins.

	FILE* details = fopen("res.txt", "a");
	FILE* res = fopen("result_iter.dat", "w");

	if (res == NULL) {
		printf("Error creating \"result_iter.dat\" file.\n");
		return FILE_ERR;
	}

	int i, j, th;

	fprintf(res, "#th d\' n_p\n");

	/*
	   Calculating all the required parameters
	 */
	for (th = 0; th < POSSIBLE_GREYS_THRESHOLDS; th++) {
		GSList* listA = NULL;
		GSList* listB = NULL;
		for (i = 0; i < d.height; i++) {
			for (j = 0; j < d.width; j++) {
				if (arr[i][j] <= th)
					listA = g_slist_prepend(listA, &arr[i][j]);
				else
					listB = g_slist_prepend(listB, &arr[i][j]);
			}
		}

		GSList* iterator = NULL;
		int sum_a = 0;
		int count_a = 0;
		int sum_b = 0;
		int count_b = 0;

		/*
		   Finding the sum of the elements of both clusters.
		 */
		for (iterator = listA; iterator; iterator = iterator->next) {
			sum_a += *((int*)(iterator->data));
			count_a++;
		}
		for (iterator = listB; iterator; iterator = iterator->next) {
			sum_b += *((int*)(iterator->data));
			count_b++;
		}

		/*
		   Calculation for Cluster A
		 */
		double mean_a = (double)sum_a / (double)count_a;
		double std_dev_A = 0;
		for (iterator = listA; iterator; iterator = iterator->next)
			std_dev_A += pow(*((int*)(iterator->data)) - mean_a, 2);
		std_dev_A = sqrt(std_dev_A / (double)count_a);

		/*
		   Calculation for Cluster B
		 */
		double mean_b = (double)sum_b / (double)count_b;
		double std_dev_B;
		for (iterator = listB; iterator; iterator = iterator->next)
			std_dev_B += pow(*((int*)(iterator->data)) - mean_b, 2);
		std_dev_B = sqrt(std_dev_B / (double)count_b);

		/*
		   Calculation for the required points
		 */
		double n_ratio = (double)count_a / (double)count_b;
		double di = (fabs(mean_a - mean_b))
			    / (sqrt(pow(std_dev_A, 2) + pow(std_dev_B, 2)));

		/*
		   Checking for invalid results
		 */
		if (isnan(di))
			di = 0;
		if (isinf(n_ratio))
			n_ratio = 0;

		fprintf(res, "%d %lf %lf\n", th, di, n_ratio);

		g_slist_free(listA);
		g_slist_free(listB);
	}

	t = clock() - t;        // Time measurement ends.
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Iterative thresholding in %lf ms\n", time_taken);
	fprintf(details, "Thresholding done in %lf ms (Iterative method)\n\n",
		time_taken);

	fclose(details);
	fclose(res);
	return 0;
}

/*
   Plots the required graphs.
 */
int plot()
{
	char* plottingA[] = { "set terminal png",
			      "set title \"th vs d\'\"",
			      "set output 'a_iter.png'",
			      "plot 'result_iter.dat' using 1:2" };
	char* plottingB[] = { "set terminal png",
			      "set title \"th vs np\"",
			      "set output 'b_iter.png'",
			      "plot 'result_iter.dat' using 1:3" };
	char* plottingC[] = { "set terminal png",
			      "set title \"d\' vs np\"",
			      "set output 'c_iter.png'",
			      "plot 'result_iter.dat' using 2:3" };

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

	pclose(gnuplotPipe);
	return 0;
}

int main(int argc, char* argv[])
{
	FILE* fp = fopen(argv[1], "r");

	//File error checking
	if (fp == NULL) {
		printf("File cannot be opened or does not exist.\n");
		return FILE_ERR;
	}

	dimensions d;
	fscanf(fp, "%d %d", &d.height, &d.width);

	int i;

	// Allocating a 2d array
	int **arr = (int**)malloc(d.height * sizeof(int**));
	for (i = 0; i < d.height; i++)
		arr[i] = (int*)malloc(d.width * sizeof(int*));

	//Reading data
	read_data(fp, arr, d);

	//Thresholding data
	threshold(arr, d);

	//Plotting graphs from the result file.
	plot();

	//Freeing memory
	for (i = 0; i < d.height; i++)
		free(arr[i]);
	free(arr);
	
	return 0;
}
