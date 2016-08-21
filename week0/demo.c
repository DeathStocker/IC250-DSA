#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* chunkify(char *s, int low, int up)
{
	char *str = malloc(sizeof(char*) * 100);
	int i;

	for (i = low; i < up; i++)
		str[i - low] = s[i];

	return str;
}

int locate_next_space(char *s, int low)
{
	int i;

	for (i = low; i < strlen(s); i++)
		if (s[i] == ' ')
			return i;
	return -1;
}

int main()
{
	printf("Enter a string : ");
	char str[100];
	scanf("%s", str);
	int low = 0;
	char matrix[25][25];
	int i = 0;
	while (locate_next_space(str, 0) != -1) {
		int pos = locate_next_space(str, low);
		char *sub = chunkify(str, low, pos);
		strcpy(matrix[i], sub);
		printf("%s\n", matrix[i]);
		i++;
		low = pos + 1;
	}
}
