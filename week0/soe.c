#include <stdio.h>

/*
 Fills the array from 1 - 100
*/
int fill_array(int arr[])
{
	int i;

	for (i = 0; i < 100; i++)
		arr[i] = i + 1;
	return 0;
}

int eliminate(int arr[])
{
	int i, j;

	for (i = 1; i < 50; i++) {
		if (arr[i] != 0) {
			int c = 2;
			j = c * arr[i] - 1;
			while (arr[j] <= 100) {
				arr[j] = 0;
				c++;
				j = c * arr[i] - 1;
			}
		}
	}

	return 0;
}

int count_prime(int arr[])
{
	int i, c = 0;

	for (i = 0; i < 100; i++)
		if (arr[i] != 0)
			c++;
	return c;
}

void display(int arr[])
{
	int i;
	int c = count_prime(arr);

	printf("There are %d prime numbers between 1 to 100 printed as follows :\n", c);
	for (i = 0; i < 100; i++)
		if (arr[i] != 0) {
			printf("%d", arr[i]);
			c--;
			if (c != 0) printf(", ");
			else printf(".\n");
		}
}

int main()
{
	int arr[100];

	fill_array(arr);
	eliminate(arr);
	display(arr);

}
