/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 2
 */

#include <stdio.h>

int move_disk(int disk, char source, char dest, char aux)
{
	int static count = 0;

	if (disk == 1) {
		count++;
		printf("[%d] Move disk %d from peg %c to peg %c.\n",
		       count, disk, source, dest);
		return count;
	}
	move_disk(disk - 1, source, aux, dest);
	count++;
	printf("[%d] Move disk %d from peg %c to peg %c.\n",
	       count, disk, source, dest);
	move_disk(disk - 1, aux, dest, source);

	return count;
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

	int count = move_disk(disk, 'A', 'C', 'B');
	printf("\nTotal number of steps required to solve this problem are = "
	       "%d\n", count);

	return 0;
}
