#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
   User defined variable for stack
 */
typedef struct _stack {
	unsigned capacity;
	int top;
	int *arr;
} stack;

#endif
