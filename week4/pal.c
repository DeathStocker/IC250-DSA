#include "pal.h"

int main()
{
	printf("Enter a string = ");
	char *s = malloc(256 * sizeof(char));
	scanf("%s", s);

	GSList* str = stackify(s, strlen(s));   //Stackifying the string.

	char* rev;
	rev = rev_string(str, strlen(s));       //Reverses the string;

	if (strcmp(s, rev) == 0)
		printf("%s is a palindrome.\n", s);
	else
		printf("%s is NOT a palindrome.\n", s);

	return 0;
}
