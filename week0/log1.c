#include <stdio.h>
#include <math.h>

int main()
{
	double x, n;

	printf("Enter the value of x : ");
	scanf("%lf", &x);
	printf("Enter the number of terms n : ");
	scanf("%lf", &n);

	double ln_x = 0;
	int i;

	for(i = 1; i <= n; i++) {
		ln_x += pow((x - 1) * 1.0 / x, i);
	}

	printf("The value of log(%d) approximated to %d terms is : %lf\n", (int)x, (int)n, ln_x);
}
