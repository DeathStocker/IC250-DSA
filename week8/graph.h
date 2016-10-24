#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <glib.h>
#include <stdbool.h>

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

// Structure to represent a min heap node
typedef struct _MinHeapNode {
	int v;
	int dist;
} MinHeapNode;

// Structure to represent a min heap
typedef struct _MinHeap {
	int size;       // Number of heap nodes present currently
	int capacity;   // Capacity of min heap
	int *pos;       // This is needed for decreaseKey()
	MinHeapNode **array;
} MinHeap;

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
MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
bool isInMinHeap(MinHeap *minHeap, int v);
void printPath(double* dist, int dest);
double* dijkstra(Graph* graph, int src);
double* bellmanford(Graph* graph, int src);

#endif
