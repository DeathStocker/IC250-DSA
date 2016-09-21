#include "c.h"

int main(int argc, char* argv[])
{
	// Verbosity for printing along with the node addresses.
	int verbose_flag = 0;
	if (argc > 1 && (strcmp(argv[1], "-v") || strcmp(argv[1], "--verbose")))
		verbose_flag = 1;
	else
		printf("Run with -v or --verbose flag for address details.\n\n");

	node *head = createList();

	if (head == NULL) {
		printf("Error encountered. Exitting.\n");
		return 1;
	}
	clear();

	// Prints original list.
	printf("Original List - \n");
	printList(head, verbose_flag);

	// Deep Copies the list.
	node *deepCopy = deepCopyList(head);

	// Print original list.
	printf("Original List After Deep Copy- \n");
	printList(head, verbose_flag);

	// Print deepCopied list.
	printf("Cloned List - \n");
	printList(deepCopy, verbose_flag);

	return 0;
}
