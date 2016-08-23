#include <stdio.h>

/*
   Prints the move to be executed for the solution
 */
void display_move(int count, char source, char dest, int disk)
{
	printf("[%d] Move the disk %d from %c to %c\n", count, disk, source, dest);
}

int solve_hanoi(int disks, stack* src, stack* aux, stack* dest)
{
	char s = 'A', d = 'B', a = 'C';

	/*
	   Interchanging destination and auxillary if number of disks is even.
	 */
	if (disks % 2 == 0) {
		char temp = d;
		d = a;
		a  = temp;
	}

	int i;
	/*
	   Pushes the larger disks first to the source.
	 */
	for (i = disks; i >= 1; i--)
		push(src, i);
}

int main()
{
	printf("Enter the number of disks = ");
	int disk;
	scanf("%d", &disk);

	if (disk < 1) {
		printf("Invalid number of disks.\n");
		return 1;
	}

	stack *src, *dest, *aux;

	/*
	   Creating 3 pegs (stacks) to hold the given number of disks.
	 */
	src = create_stack(disk);
	aux = create_stack(disk);
	dest = create_stack(disk);

	solve_hanoi(disk, src, aux, dest);
	return 0;
}
