#include "stack.h"

int transfer_stack(stack* src, stack* dest)
{
	int count = 0;

	while (is_empty(src) != 1) {
		int val = pop(src);
		push(dest, val);
		count++;
	}

	return count;
}

int process_queue(stack* queue, stack* temp, int ch)
{

	int val = 0;

	int isFull = is_full(queue);
	int isEmpty = is_empty(queue);

	switch (ch) {
	case 0:
		printf("\nExitting.\n");
		return 1;
		break;
	case 1:
		if (isFull == 1)
			printf("\nSorry the queue is full. Please pop/empty"
			       " it before pushing.\n");
		else {
			printf("\nEnter the value to be pushed = ");
			scanf("%d", &val);
			transfer_stack(queue, temp);
			push(queue, val);
			transfer_stack(temp, queue);
		}
		break;
	case 2:
		if (isEmpty == 1)
			printf("\nSorry the queue is empty. Please fill"
			       " it before popping.\n");
		else {
			int val = pop(queue);
			printf("\n%d popped.\n", val);
		}
		break;
	case 3:
		if (isEmpty == 1)
			printf("\nSorry the queue is empty. Please fill"
			       " it before viewing the top.\n");
		else {
			val = pop(queue);
			push(queue, val);
			printf("The top value is = %d\n", val);
		}
		break;
	case 4:
		if (isEmpty == 1)
			printf("\nSorry the queue is empty. Please fill"
			       " it before emptying the queue.\n");
		else {
			printf("\nEmptying queue.\n");
			while (is_empty(queue) != 1)
				printf("%d\n", pop(queue));
			printf("\nQueue emptied.\n");
		}
		break;
	case 5:
		if (isEmpty == 1)
			printf("\nSorry the queue is empty. Please fill"
			       " it before displaying its contents.\n");
		else {
			printf("\nElements in queue = \n");
			while (is_empty(queue) != 1) {
				val = pop(queue);
				printf("%d\n", val);
				push(temp, val);
			}
			transfer_stack(temp, queue);
		}
		break;
	case 6:
		printf("\nCount = %d\n", transfer_stack(queue, temp));
		transfer_stack(temp, queue);
		break;
	case 7:
		free(queue);
		free(temp);
		return 1;
	default:
		printf("\nWrong Choice. Try Again.\n");
	}

	return 0;
}

int input(stack* queue, stack* temp)
{
	while (1) {
		printf("===============================================");
		printf("\nChoose what you want to do with your queue -\n");
		printf("\n 1 - Push");
		printf("\n 2 - Pop");
		printf("\n 3 - Top");
		printf("\n 4 - Empty");
		printf("\n 5 - Display");
		printf("\n 6 - Queue Count");
		printf("\n 7 - Destroy Queue and Exit.");
		printf("\n\n [0] - Exit");
		printf("\n===============================================");

		printf("\n\nChoice = ");
		int ch;
		scanf("%d", &ch);

		clear();

		if (process_queue(queue, temp, ch) == 1)
			break;
	}
	return 0;
}

int main()
{
	printf("Enter the size of the queue = ");
	unsigned size;
	scanf("%d", &size);

	if (size < 1) {
		printf("Invalid size of the queue.\n");
		return 1;
	}

	stack* queue = create_stack(size);
	stack* temp = create_stack(size);

	input(queue, temp);

	return 0;
}
