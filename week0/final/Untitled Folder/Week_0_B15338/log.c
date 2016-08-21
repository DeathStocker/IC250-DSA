#include <stdio.h>
#include <math.h>

int main()
{
	/*
	   User input.
	 */
	double x, n;

	printf("Enter the value of x : ");
	scanf("%lf", &x);
	printf("Enter the number of terms n : ");
	scanf("%lf", &n);

	double ln_x = 0;
	int i;
	/*
	   Calculation using the given formula
	 */
	for (i = 1; i <= n; i++)
		ln_x = ln_x + ((1 / (double)i) * pow(((x - 1) / x), i));

	printf("The value of log(%d) approximated to %d terms is : %lf\n", (int)x, (int)n, ln_x);

	return 0;
}
