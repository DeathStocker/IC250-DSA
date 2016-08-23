#include "stack.h"

/*
   Checks if the stack is full or not.
 */
int is_full(stack* s)
{
	if (s->top == (signed)s->capacity - 1)
		return 1;
	return 0;
}

/*
   Checks if the stack is empty or not.
 */
int is_empty(stack* s)
{
	if (s->top == -1)
		return 1;
	return 0;
}
