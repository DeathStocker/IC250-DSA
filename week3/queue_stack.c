#include "stack.h"

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

	int val = 0;

	switch(ch) {
		case 1:
		printf("Enter value to be pushed = ");
		scanf("%d", &val);

	}
}
