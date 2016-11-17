// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 6

#ifndef C_H
#define C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

typedef struct _node {
	int label;
	struct _node* next;
	struct _node* random;
} node;

node* createNode(int label);
node* deepCopyList(node *head);
void printList(node *head, int verbose_flag);
node* createList();

#endif
