/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#ifndef FAST_TRANSPOSE_H
#define FAST_TRANSPOSE_H

#include <stdio.h>
#include <stdlib.h>

#define FILE_ERR 1

/*
   Dimensions for the input matrix
 */
typedef struct _dimension {
	int row;
	int col;
} dimension;

/*
   Contains the row and column frequencies of the elements.
 */
typedef struct _frequencies {
	int* row_freq;
	int* col_freq;
} frequencies;

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

void displayTuple(tuple* element, int* size);

int makeCumFrequency(int* arr, int size);

void addTuple(tuple* element, int* size_tuple, int index, int x, int y, int val);

int isTupleEmpty(tuple tup);

tuple* fastTranspose(tuple* element, int size, dimension* d);

int makeTuples(frequencies* freq, tuple* element, int* size_tuple,
	       int* count, int val, int i, int j);

int readMatrix(FILE* fp, tuple* element, int* size_tuple, frequencies* freq,
	       dimension* d);

#endif
