/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#include "fast_transpose.h"

int main(int argc, char* argv[])
{
	(void)argc;     // Silencing the unused variable warning.

	FILE* fp = fopen(argv[1], "r");

	// File error checking
	if (fp == NULL) {
		printf("File cannot be opened or does not exist.\n");
		return FILE_ERR;
	}

	dimension* d = malloc(sizeof(dimension));
	fscanf(fp, "%d%d", &d->row, &d->col);

	frequencies* freq = malloc(sizeof(frequencies));
	freq->row_freq = malloc((d->row + 1) * sizeof(int));
	freq->col_freq = malloc((d->col + 1) * sizeof(int));
	freq->row_freq[0] = 0;
	freq->col_freq[0] = 0;

	tuple* element = malloc(100 * sizeof(tuple));
	int* size_tuple = malloc(sizeof(int));
	*size_tuple = 0;

	if (readMatrix(fp, element, size_tuple, freq, d) == 1)
		return 1;
	displayTuple(element, size_tuple);

	tuple* trans = fastTranspose(element, *size_tuple, d);

	displayTuple(trans, size_tuple);

	free(element);
	free(size_tuple);
	free(d);
	free(fp);
	free(trans);

	return 0;
}
