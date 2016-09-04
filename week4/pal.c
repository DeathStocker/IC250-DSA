#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

GSList* stackify(char* s, int length)
{
	GSList* str = NULL;
	int i;

	for (i = 0; i < length; i++)
		str = g_slist_prepend(str, &s[i]);

	return str;
}

char* rev_string(GSList* str, int length)
{
	char* rev = malloc(length * sizeof(char));

	int i;
	GSList* iterator;
	for (iterator = str, i = 0; iterator && i < length; iterator = iterator->next, i++)
		rev[i] = *((char*)(iterator->data));
	rev[i] = '\0';

	return rev;
}

int main()
{
	printf("Enter a string = ");
	char *s = malloc(256 * sizeof(char));
	scanf("%s", s);

	GSList* str = stackify(s, strlen(s));
	char* rev;

	rev = rev_string(str, strlen(s));

	if (strcmp(s, rev) == 0)
		printf("%s is a palindrome.\n", s);
	else
		printf("%s is NOT a palindrome.\n", s);

	return 0;
}
