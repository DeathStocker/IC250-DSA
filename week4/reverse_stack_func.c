/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#include "reverse_stack.h"

int* remove_bottom(Stack* stack)
{
	int* val = stack_pop(stack);

	if (is_empty(stack))
		return val;
	else {
		int* a = remove_bottom(stack);
		stack_push(stack, val);
		return a;
	}
}

void reverse_stack(Stack* stack)
{
	if (is_empty(stack))
		return;
	int* val = remove_bottom(stack);

	reverse_stack(stack);

	stack_push(stack, val);
}
