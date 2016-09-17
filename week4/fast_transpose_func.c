/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#include "fast_transpose.h"

/*
   Displays the tuples
 */
void displayTuple(tuple* element, int* size)
{
	printf("\nTuples = \n");
	int i;
	for (i = 0; i < *size; i++)
		printf("<(%d, %d), %d>\n", element[i].pos.x, element[i].pos.y,
		       element[i].val);
}

/*
   Makes Cumulative Frequency table from a regular frequency table.
 */
int makeCumFrequency(int* arr, int size)
{
	int i;

	for (i = 1; i < size; i++)
		arr[i] += arr[i - 1];

	return 0;
}

/*
   Adds a tuple to the list.
 */
void addTuple(tuple* element, int* size_tuple, int index, int x, int y, int val)
{
	element[index].pos.x = x;
	element[index].pos.y = y;
	element[index].val = val;
	(*size_tuple)++;
}

/*
   Checks if the tuple is empty or not.
 */
int isTupleEmpty(tuple tup)
{
	if (tup.val == 0)
		return 0;
	return 1;
}

/*
   Fast transposes the sparse array.
 */
tuple* fastTranspose(tuple* element, int size, dimension* d)
{
	int i;

	tuple* trans = malloc(100 * sizeof(tuple));

	int* col_count = malloc((d->col) * sizeof(int));

	for (i = 0; i < d->col; i++)
		col_count[i] = 0;

	for (i = 0; i < size; i++) {
		int ex = element[i].pos.x;
		int ey = element[i].pos.y;
		int eval = element[i].val;
		trans[ey + col_count[ey]].pos.x = ey;
		trans[ey + col_count[ey]].pos.y = ex;
		trans[ey + col_count[ey]].val = eval;
		int j;
		for (j = ey + 1; j < d->col; j++)
			col_count[j] = col_count[j - 1] + col_count[j];
	}

	return trans;

}

/*
   Makes the list of the tuples.
 */
int makeTuples(frequencies* freq, tuple* element, int* size_tuple,
	       int* count, int val, int i, int j)
{
	if (val != 0) {
		freq->row_freq[i + 1]++;
		freq->col_freq[j + 1]++;
		(*count)++;

		if (element != NULL)
			addTuple(element, size_tuple, (*count - 1), i, j, val);
		else {
			printf("Error (re)allocating memory.\n");
			return 1;
		}
	}

	return 0;
}

/*
   Reads data from the file and stores the frequency of the values.
 */
int readMatrix(FILE* fp, tuple* element, int* size_tuple, frequencies* freq,
	       dimension* d)
{

	int i, j, count = 0;

	for (i = 0; i < d->row; i++)
		for (j = 0; j < d->col; j++) {
			int val;
			fscanf(fp, "%d", &val);

			if (makeTuples(freq, element, size_tuple, &count,
				       val, i, j) == 1)
				return 1;
		}
	makeCumFrequency(freq->row_freq, (d->row) + 1);
	makeCumFrequency(freq->col_freq, (d->col) + 1);
	return 0;
}
