/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 3 (File taken from Week - 2)
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

/*
   User defined variable for stack
 */
typedef struct _stack {
	unsigned capacity;
	int top;
	int *arr;
} stack;

stack* create_stack(unsigned capacity);

int is_full(stack* s);

int is_empty(stack* s);

int push(stack *s, int item);

int pop(stack* s);

#endif
