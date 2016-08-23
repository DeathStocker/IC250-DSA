#include <stdio.h>

/*
   Prints the move to be executed for the solution
 */
void display_move(int count, char source, char dest, int disk)
{
	printf("[%d] Move the disk %d from %c to %c\n", count, disk, source, dest);
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
