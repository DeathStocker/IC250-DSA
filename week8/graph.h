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

typedef struct _Edge {
	int dest;
	double weight;
} Edge;

typedef struct _DoubleEdge {
	int source;
	int dest;

	double weight;
} DoubleEdge;

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

AdjListNode* newAdjListNode(int src, int dest, double weight);
Graph* createGraph(int V, int is_directed);
void addEdge(Graph* graph, int src, int dest, double weight);
void deleteEdge(Graph* g, int src, int dest);
void printGraph(Graph* graph);
int degreeVertex(Graph* g, int V);
int* neighboursVertex(Graph* g, int V);
int DFS(Graph* g, int V, int* visited);
int do_DFS(Graph* g, int V);
int do_BFS(Graph* g, int V);
int MinDistance(double* distances, gboolean* processed, int size);
Graph* primMST(Graph* graph, int source, int is_directed);
gint EdgeCompareFunction(gconstpointer a, gconstpointer b);
Graph* KruskalMST(Graph* graph, int source, int is_directed);

#endif
