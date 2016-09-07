#include "stack_queue.h"

/*
   Pops the element from the queue as a stack.
 */
int* popStack_Queue(GQueue* src, GQueue* dest)
{
	int* val;

	while (getQueueLength(src) > 1) {
		val = (int*)(popQueue(src));
		pushQueue(dest, val);
	}

	int* top = (int*)(popQueue(src));

	while (!(isQueueEmpty(dest))) {
		val = (int*)(popQueue(dest));
		pushQueue(src, val);
	}

	return top;
}

/*
   Transfers the elements from one queue to another
 */
int transfer_queue(GQueue* src, GQueue* dest)
{
	while (!(isQueueEmpty(src))) {
		int* val = popStack_Queue(src, dest);
		pushQueue(dest, val);
	}

	return 0;
}

/*
   Processes the queue according to the users choice.
 */
int process_queue(GQueue* stack, GQueue* temp, int ch)
{

	int* val;

	switch (ch) {
	case 0:	// Exit.
		printf("\nExitting.\n");
		return 1;
		break;
	case 1:	// Push.
		val = malloc(sizeof(int));
		printf("\nEnter the value to be pushed = ");
		scanf("%d", val);
		pushQueue(stack, val);
		break;
	case 2:	// Pop.
		if (isQueueEmpty(stack))
			printf("\nSorry the stack is empty. Please fill"
			       " it before popping.\n");
		else
			printf("\n%d popped.\n", *(popStack_Queue(stack, temp)));
		break;
	case 3:	// Top.
		if (isQueueEmpty(stack))
			printf("\nSorry the stack is empty. Please fill"
			       " it before viewing the top.\n");
		else
			printf("\nThe top value is = %d\n", *(int*)(peekQueue(stack)));
		break;
	case 4: // Empty.
		if (isQueueEmpty(stack))
			printf("\nSorry the stack is empty. Please fill"
			       " it before emptying the stack.\n");
		else {
			printf("\nEmptying stack.\n");
			while (!(isQueueEmpty(stack)))
				printf("%d\n", *(popStack_Queue(stack, temp)));
			printf("\nQueue emptied.\n");
		}
		break;
	case 5: // Display
		if (isQueueEmpty(stack))
			printf("\nSorry the stack is empty. Please fill"
			       " it before displaying its contents.\n");
		else {
			printf("\nElements in stack = \n");

			int count = getQueueLength(stack);
			GQueue* copy = copyQueue(stack);
			while (count > 0) {
				val = popStack_Queue(copy, temp);
				printf("%d\n", *val);
				count--;
			}
			g_queue_free(copy);
		}
		break;
	case 6: // Count.
		printf("\nCount = %d\n", getQueueLength(stack));
		break;
	case 7: // Free.
		g_queue_free(stack);
		g_queue_free(temp);
		return 1;
	default:
		printf("\nWrong Choice. Try Again.\n");
	}

	return 0;
}

/*
   Takes input from the user in a menu format.
 */
int input(GQueue* stack, GQueue* temp)
{
	while (1) {
		printf("===============================================");
		printf("\nChoose what you want to do with your stack -\n");
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

		clear();        // Clears the screen

		if (process_queue(stack, temp, ch) == 1)
			break;
	}
	return 0;
}
