#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	printf("Enter a sentence : ");
	char s[100];
	scanf("%[^\n]s", s);    // Inputs all characters until newline character.
	char str[100];
	strcpy(str, s);         // Copied value for future use.

	char* word;
	word = strtok(s, " ,.?!");
	char arr[20][20];       //array of words
	int i = 0;
	while (word != NULL) {
		strcpy(arr[i], word);
		i++;
		word = strtok(NULL, " ,.?!");   //switching to the next word
	}
	int count = i - 1;
	int flag = 0;
	for (i = 0; i <= count / 2; i++) {
		if (strcmp(arr[count - i], arr[i]) != 0)        //comparing equidistant
			                                        //words from opposite ends.
			break;
		else flag = 1;
	}

	if (flag == 1)
		printf("\"%s\" is a Palindrome paragraph.\n", str);
	else
		printf("\"%s\" is NOT a Palindrome paragraph.\n", str);
	return 0;
}
