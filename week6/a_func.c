// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 6

#include "a.h"

void swapPointers(int* a, int* b)
{
	int c = *a;

	*a = *b;
	*b = c;
}

void printPointerValue(int* a)
{
	printf("%d", *a);
}

int compareIntegers(int* a, int* b)
{
	if (*a > *b)
		return 1;
	return 0;
}

int compareStrings(char* a, char* b)
{
	int i = 0;

	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] < b[i])
			return 1;
		i++;
	}

	return 0;
}

void countTillThisNum(int num)
{
	int* ptr = &num;

	if (*ptr == 0)
		return;
	countTillThisNum(*ptr - 1);
	printf("%d\n", *ptr);
}
