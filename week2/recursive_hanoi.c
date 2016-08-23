#include <stdio.h>

int move_disk(int disk, char source, char dest, char aux)
{
	if(disk == 1) {
		printf("Move disk %d from peg %c to peg %c.\n", disk, source, dest);
		return 0;
	}
	move_disk(disk - 1, source, aux, dest);
	printf("Move disk %d from peg %c to peg %c.\n", disk, source, dest);
	move_disk(disk - 1, aux, dest, source);

	return 0;
}

int main()
{
	printf("Enter the number of disks = ");
	int disk;
	scanf("%d", &disk);

	move_disk(disk, 'A', 'B', 'C');

	return 0;
}
