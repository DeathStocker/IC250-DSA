#include "c.h"

/*
   Creates a node with next and random pointers.
 */
node* createNode(int label)
{
	node* newNode = malloc(sizeof(node));

	newNode->label = label;
	newNode->next = NULL;
	newNode->random = NULL;

	return newNode;
}

/*
   Deep Copies the List.
 */
node* deepCopyList(node *head)
{
	if (head == NULL)
		return NULL;

	/*
	   Copies the current node and adds it between the current and the next node.
	 */
	node* iterator = head;
	while (iterator != NULL) {
		node* deepCopy = createNode(iterator->label);

		deepCopy->next = iterator->next;
		iterator->next = deepCopy;

		iterator = iterator->next->next;
		// Moves to two nodes ahead as we have just inserted one in between.
	}

	/*
	   Sets the random pointers of the original list.
	 */
	iterator = head;
	while (iterator != NULL) {
		iterator->next->random = iterator->random->next;
		iterator = iterator->next->next;
	}

	/*
	   Seperates the original and the deepCopied list.
	 */
	iterator = head;
	node *deepCopiedHead = iterator->next;
	node *deepCopied = deepCopiedHead;
	while (iterator != NULL) {
		iterator->next = iterator->next->next;
		iterator = iterator->next;

		if (deepCopied->next) {
			deepCopied->next = deepCopied->next->next;
			deepCopied = deepCopied->next;
		}
	}

	return deepCopiedHead;
}

void printList(node *head, int verbose_flag)
{
	node *iterator = head;

	int i = 1;

	while (iterator != NULL) {
		if (verbose_flag == 0)
			printf("[%d] %d [Random-> %d ]\n", i, iterator->label,
			       iterator->random->label);
		else
			printf("[%d] %d (%p)\t[Random-> %d (%p)]\n", i,
			       iterator->label, iterator, iterator->random->label,
			       iterator->random);
		iterator = iterator->next;
		i++;
	}
	printf("\n");
}

node* createList()
{
	int i = 1;
	node* head = createNode(0);

	if (head == NULL) {
		clear();
		printf("Could not allocate memory for the list.\n");
		return NULL;

	}
	node* iterator = head;

	printf("Enter the labels of the nodes [+ve Integers] - \nEnter [0] or"
	       " [-ve int] to EXIT.\n\n");
	while (1) {
		printf("[%d] Node Value = ", i);
		int val;
		scanf("%d", &val);

		if (val <= 0)
			break;

		iterator->next = createNode(val);
		iterator = iterator->next;
		i++;
	}

	int num_nodes = i - 1;

	if (num_nodes == 0) {
		clear();
		printf("No elements in the list.\n");
		return NULL;
	}

	head = head->next;

	i = 1;
	iterator = head;
	printf("\n\nEnter the position to point the random pointers to - \n");
	while (iterator) {
		int position;
		printf("[%d] Random Position = ", i);
		scanf("%d", &position);

		if (position > num_nodes || position < 1) {
			clear();
			printf("Position is invalid.\n");
			return NULL;
		}

		node* iter;
		int j = 1;

		// Gets the address of the node at the given position.
		for (iter = head; iter != NULL && j < position; iter = iter->next, j++) ;

		iterator->random = iter;
		iterator = iterator->next;
		i++;
	}

	return head;
}
