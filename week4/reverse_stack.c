#include "reverse_stack.h"

int main()
{
	Stack* stack = stack_new();
	int* val = malloc(sizeof(int));

	*val = -1;

	printf("Enter [0] to EXIT.\n");

	int count = 1;
	while (*val != 0) {
		printf("[%d] Enter a number = ", count);
		val = malloc(sizeof(int));
		scanf("%d", val);

		stack_push(stack, val);
		count++;
	}

	stack_pop(stack);

	Stack* iterator;

	reverse_stack(stack);

	printf("\nReversed Stack - \n\n");
	for (iterator = stack, count = 1; iterator->head; iterator = stack , count++)
		printf("[%d] = %d\n", count, *(int*)(stack_pop(stack)));

	return 0;
}
