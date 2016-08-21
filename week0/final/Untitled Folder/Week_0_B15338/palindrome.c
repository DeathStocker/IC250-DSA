#include <stdio.h>
#include <string.h>

/*
   Reverses the passed string
 */
int rev_string(char str[512])
{
	int len = strlen(str);
	char rev[len];
	int i;

	for (i = 0; i < len; i++)
		rev[i] = str[len - 1 - i];
	rev[len] = '\0';
	strcpy(str, rev);
	return 0;
}

int main()
{
	printf("Enter the string to be checked as Palindrome : \n");
	char inp[512];
	scanf("%s", inp);
	char str[512];
	strcpy(str, inp);

	rev_string(str);
	if (strcmp(str, inp) == 0) //comparing the original and reversed string.
		printf("%s is a Palindrome string.\n", inp);
	else
		printf("%s is NOT a Palindrome string.\n", inp);
}
