#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <glib.h>

#define INFINITE INT_MAX
#define clear() printf("\033[H\033[J")

// A structure to represent an adjacency list node
typedef struct _AdjListNode {
	int src;
	int dest;
	double weight;
	struct _AdjListNode* next;
} AdjListNode;

// A structure to represent an adjacency list
typedef struct _AdjList {
	AdjListNode* head; // pointer to head node of list
} AdjList;

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
typedef struct _Graph {
	int V;
	int E;
	AdjList* array;
	int directed;
} Graph;

#endif
