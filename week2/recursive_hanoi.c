#include <stdio.h>

int move_disk(int disk, char source, char dest, char aux)
{
	if(disk == 1) {
		printf("Move disk %d from peg %c to peg %c.\n", disk, source, dest);
	}
	move_disk(disk - 1, source, aux, dest);
	printf("Move disk %d from peg %c to peg %c.\n", disk, source, dest);
	move_disk(disk - 1, aux, dest, source);

	return 0;
}
