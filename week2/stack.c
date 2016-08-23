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

/*
   "Pushes" the given value to the top of the stack and changes the top.
 */
int push(stack *s, int value)
{
	if (is_full(s))
		return -1;
	s->arr[++s->top] = value;

	return 0;
}

/*
   "Pops" the topmost item from the stack.
 */
int pop(stack* s)
{
	if (is_empty(s) == 1)
		return -1;
	int value = s->arr[s->top];
	s->top--;
	return value;
}

/*
   Creates a stack of the given capacity.
 */
stack* create_stack(unsigned capacity)
{
	stack* s = (stack*)malloc(sizeof(stack));

	s->capacity = capacity;
	s->top = -1;
	s->arr = (int*)malloc(s->capacity * sizeof(int));

	return s;
}
