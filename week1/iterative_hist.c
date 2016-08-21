/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
   Reads data from the file and stores the frequency of the values.
 */
int* read_data(FILE* fp, int* freq, dimensions d)
{
	clock_t t;
	double time_taken;
	int i, j;

	t = clock();     // Time measurement begins.

	FILE* details = fopen("res.txt", "a");

	for (i = 0; i < d.height; i++)
		for (j = 0; j < d.width; j++) {
			int val;
			fscanf(fp, "%d", &val);
			freq[val]++;
		}

	t = clock() - t;        // Time measurement ends.
	time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Data read in %lf ms\n", time_taken);
	fprintf(details, "Data read in %lf ms (Histogram method)\n", time_taken);

	fclose(details);
	return freq;
}

/*
   Divides the points in the image into two clusters for varying thresholds
   and calculates discriminative index and ratio of number of points for each.
 */
int threshold(FILE* fp, int* arr, dimensions d)
{
	clock_t t;

	FILE* details = fopen("res.txt", "a");

	FILE* res = fopen("result_hist.dat", "w");

	fprintf(res, "#th d' np\n");
	int* freq = read_data(fp, arr, d);

	t = clock();    // Time measurement begins.

	int i, j;

	/*
	   Calculating all the required parameters
	 */
	for (i = 0; i < POSSIBLE_GREYS_THRESHOLDS; i++) {
		int sum_a = 0;
		int sum_b = 0;
		int count_a = 0;
		int count_b = 0;

		/*
		   Finding the sum of the elements of both clusters.
		 */
		for (j = 0; j <= i; j++) {
			sum_a += (j * freq[j]);
			count_a += freq[j];
		}
		for (j = i + 1; j < POSSIBLE_GREYS_THRESHOLDS; j++) {
			sum_b += (j * freq[j]);
			count_b += freq[j];
		}

		/*
		   Calculation for Cluster A
		 */
		double mean_a = (double)sum_a / (double)count_a;
		double std_dev_A = 0;
		for (j = 0; j <= i; j++)
			std_dev_A += freq[j] * pow(j - mean_a, 2);
		std_dev_A = sqrt(std_dev_A / (double)count_a);

		/*
		   Calculation for Cluster B
		 */
		double mean_b = (double)sum_b / (double)count_b;
		double std_dev_B = 0;
		for (j = i + 1; j < POSSIBLE_GREYS_THRESHOLDS; j++)
			std_dev_B += freq[j] * pow(j - mean_b, 2);
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

		fprintf(res, "%d %lf %lf\n", i, di, n_ratio);
	}

	t = clock() - t;        // Time measurement ends.
	double time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
	printf("Thresholding done in %lf ms\n", time_taken);
	fprintf(details, "Thresholding done in %lf ms (Histogram method)\n\n",
		time_taken);

	fclose(details);
	fclose(res);
	return 0;
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
			      "set title \"th vs d\'\"",
			      "set output 'a_hist.png'",
			      "plot 'result_iter.dat' using 1:2" };
	char* plottingB[] = { "set terminal png",
			      "set title \"th vs np\"",
			      "set output 'b_hist.png'",
			      "plot 'result_iter.dat' using 1:3" };
	char* plottingC[] = { "set terminal png",
			      "set title \"d\' vs np\"",
			      "set output 'c_hist.png'",
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

	// File error checking
	if (fp == NULL) {
		printf("File cannot be opened or does not exist.\n");
		return FILE_ERR;
	}

	dimensions d;
	fscanf(fp, "%d %d", &d.height, &d.width);

	int freq[POSSIBLE_GREYS_THRESHOLDS];

	int i;
	// Initializing the frequency array elements.
	for (i = 0; i < POSSIBLE_GREYS_THRESHOLDS; i++)
		freq[i] = 0;

	// Reading data
	threshold(fp, freq, d);

	// Plotting graphs from the results file.
	plot();

	return 0;
}
