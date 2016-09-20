#ifndef B_H
#define B_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int** maker(int n, int m);
void writer(int** matrix, int n, int m, char* filename);
void printDelete(int** matrix, int n, int m);

#endif
