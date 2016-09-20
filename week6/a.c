#include "a.h"

int main()
{
	printf("Enter a and b\n");
	int* a = malloc(sizeof(int));
	int* b = malloc(sizeof(int));
	scanf("%d", a);
	scanf("%d", b);

	printf("\na = ");
	printPointerValue(a);
	printf("\nb = ");
	printPointerValue(b);

	printf("\n\nAfter swapping - \n");
	swapPointers(a, b);
	printf("\na = ");
	printPointerValue(a);
	printf("\nb = ");
	printPointerValue(b);

	printf("\n\n%c is bigger.\n", (!compareIntegers(a, b)) ? 'a' : 'b');

	free(b);

	printf("Enter two strings\n");
	char s1[256], s2[256];

	scanf("%s", s1);
	scanf("%s", s2);

	printf("\n\nString %c comes first.\n", (compareStrings(s1, s2)) ? '1' : '2');

	printf("\nEnter a number.\n");
	scanf("%d", a);

	printf("\nSeries = \n");
	countTillThisNum(*a);
	free(a);

	return 0;
}
