#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <stdbool.h>

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

MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
bool isInMinHeap(MinHeap *minHeap, int v);
void printArr(double dist[], int n);
void dijkstra(Graph* graph, int src, int dest);

#endif
