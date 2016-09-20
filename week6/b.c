#include "b.h"

int main(int argc, char* argv[])
{
	if(argc != 3) {
		printf("Enter the number of rows and columns of the matrix. (Only)\n");
		return 1;
	}

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	int** arr = maker(n, m);
	writer(arr, n, m, "b.dat");
	printDelete(arr, n, m);

	return 0;
}
