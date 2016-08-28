#include "stack.h"

int transfer_stack(stack* src, stack* dest)
{
	while(is_empty(src) != -1) {
		int val = pop(src);
		push(dest, val);
	}

	return 0;
}

int process_queue(stack* queue, stack* temp, int ch)
{

	int val = 0;

	switch (ch) {
	case 1:
		if (is_full(queue) == 1)
			printf("Sorry the queue is full. Please pop/empty"
			       " it before pushing.\n");
		else {
			printf("Enter the value to be pushed =");
			scanf("%d", &val);
			transfer_stack(queue, temp);
			push(queue, val);
			transfer_stack(temp, queue);
		}

	}

	return 0;
}

int input(stack* queue, stack* temp)
{
	while (1) {
		printf("\nChoose what you want to do with your queue -\n");
		printf("\n 1 - Push");
		printf("\n 2 - Pop");
		printf("\n 3 - Top");
		printf("\n 4 - Empty");
		printf("\n 5 - Exit");
		printf("\n 6 - Display");
		printf("\n 7 - Stack Count");
		printf("\n 8 - Destroy Stack");
		printf("\n\nChoice = ");

		int ch;
		scanf("%d", &ch);

		if(process_queue(queue, temp, ch) == 1)
			break;
		else
			return 1;
	}
	return 0;
}

int main()
{
	printf("Enter the size of the queue = ");
	unsigned size;
	scanf("%d", &size);

	if (size < 1) {
		printf("Invalid size of queue.\n");
		return 1;
	}

	stack* queue = create_stack(size);
	stack* temp = create_stack(size);

	input(queue, temp);

	return 0;
}
