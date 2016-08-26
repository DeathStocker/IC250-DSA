/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 1
 */

#include "stack.h"

/*
   Prints the move to be executed for the solution
 */
void display_move(int count, char source, char dest, int disk)
{
	printf("[%d] Move the disk %d from %c to %c\n", count, disk, source, dest);
}

/*
   Legally moves the disk from source to destination or the other way around.
 */
int move_disk(int count, stack* src, stack* dest, char s, char d)
{
	int src_top = pop(src);
	int dest_top = pop(dest);

	/*
	   -1 denotes an empty stack/peg.
	   The following basically put a smaller disk on a bigger disk
	   or any sized disk in an already empty peg.
	 */
	if (src_top == -1) {
		push(src, dest_top);
		display_move(count, d, s, dest_top);
	} else if (dest_top == -1) {
		push(dest, src_top);
		display_move(count, s, d, src_top);
	} else if (src_top > dest_top) {
		push(src, src_top);
		push(src, dest_top);
		display_move(count, d, s, dest_top);
	} else {
		push(dest, dest_top);
		push(dest, src_top);
		display_move(count, s, d, src_top);
	}

	return 0;
}

/*
   Solves the Tower of Hanoi iteratively.
 */
int solve_hanoi(int disks, stack* src, stack* aux, stack* dest)
{
	char s = 'A', d = 'B', a = 'C'; // Source, destination, and auxillary pegs.

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

	/*
	   Checks the position of the current peg and changes the source,
	   destination, and auxillary pegs accordingly.
	 */
	int no_of_moves = pow(2, disks) - 1;
	for (i = 1; i <= no_of_moves; i++) {
		if (i % 3 == 1)
			move_disk(i, src, dest, s, d);

		else if (i % 3 == 2)
			move_disk(i, src, aux, s, a);

		else if (i % 3 == 0)
			move_disk(i, aux, dest, a, d);
	}
	printf("\nTotal number of steps required to solve this problem are = "
	       "%d\n", no_of_moves);

	return 0;
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
