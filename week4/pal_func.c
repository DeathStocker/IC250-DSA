#include "pal.h"

/*
   Stackifies the string with each element equal to the corresponding character
   in the string.
 */
GSList* stackify(char* s, int length)
{
	GSList* str = NULL;
	int i;

	for (i = 0; i < length; i++)
		str = g_slist_prepend(str, &s[i]);

	return str;
}

/*
   Reverses the stackified string.
 */
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
