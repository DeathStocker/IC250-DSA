#include <stdio.h>
#include <stdlib.h>

/*
   Fills the array from 1 - 10
 */
int fill_array(int* arr)
{
	int i;

	for (i = 0; i < 100; i++)
		*(arr + i) = i + 1;
	return 0;
}

/*
   Eliminates the multiples of the prime numbers by checking the first half
   of the array.
 */
int eliminate(int* arr)
{
	int i, j;       //loop variables

	for (i = 1; i < 50; i++) {
		if (*(arr + i) != 0) {
			int c = 2;                      //counter for multiples
			j = c * (*(arr + i)) - 1;       // position of first integral multiple of current number.
			while (j < 100) {
				*(arr + j) = 0;
				c++;
				j = c * (*(arr + i)) - 1; // position of next integral multiple of current number.
			}
		}
	}

	return 0;
}

/*
   Counts the number of prime numbers found
 */
int count_prime(int arr[])
{
	int i, c = 0; // Loop and counter variable.

	for (i = 0; i < 100; i++)
		if ((*(arr + i)) != 0)
			c++;
	return c;
}

/*
   Displays the prime numbers found.
 */
void display(int arr[])
{
	int i;
	int c = count_prime(arr);

	printf("There are %d prime numbers between 1 to 10 printed as follows :\n", c);
	for (i = 0; i < 100; i++)
		if ((*(arr + i)) != 0) {
			printf("%d", *(arr + i));
			c--;                    //decreasing counter to get
			                        //position for placing full
			                        //stop in the output.
			if (c != 0)
				printf(", ");
			else
				printf(".\n");     //formatting for printing.
		}
}

int main()
{
	int* arr = malloc(sizeof(int) * 100);

	fill_array(arr);
	eliminate(arr);
	display(arr);

	free(arr);

	return 0;
}
