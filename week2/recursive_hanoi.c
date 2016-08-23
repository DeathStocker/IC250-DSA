#include <stdio.h>

int move_disk(int disk, char source, char dest, char aux)
{
	int static count = 1;
	if(disk == 1) {
		printf("[%d] Move disk %d from peg %c to peg %c.\n", count, disk, source, dest);
		count++;
		return count - 1;
	}
	move_disk(disk - 1, source, aux, dest);
	printf("[%d] Move disk %d from peg %c to peg %c.\n", count, disk, source, dest);
	count++;
	move_disk(disk - 1, aux, dest, source);

	return count - 1;
}

int main()
{
	printf("Enter the number of disks = ");
	int disk;
	scanf("%d", &disk);

	int count = move_disk(disk, 'A', 'C', 'B');
	printf("\nTotal number of steps required to solve this problem are = %d\n", count);
	return 0;
}
