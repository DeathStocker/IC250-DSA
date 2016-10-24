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

// A utility function to create a new adjacency list node
AdjListNode* newAdjListNode(int src, int dest, double weight)
{
	AdjListNode* newNode = malloc(sizeof(AdjListNode));

	newNode->src = src;
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates a graph of V vertices
Graph* createGraph(int V, int is_directed)
{
	Graph* graph = malloc(sizeof(Graph));

	graph->V = V;
	graph->E = 0;
	graph->directed = is_directed;

	// Create an array of adjacency lists.  Size of array will be V
	graph->array = malloc(V * sizeof(AdjList));

	// Initialize each adjacency list as empty by making head as NULL
	int i;
	for (i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, double weight)
{
	// Add an edge from src to dest.  A new node is added to the adjacency
	// list of src.  The node is added at the begining
	AdjListNode* newNode = newAdjListNode(src, dest, weight);

	graph->E = graph->E + 1;

	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	if (graph->directed == 0) {
		newNode = newAdjListNode(dest, src, weight);
		newNode->next = graph->array[dest].head;
		graph->array[dest].head = newNode;
	}
}

void deleteEdge(Graph* g, int src, int dest)
{
	AdjListNode* iterator = g->array[src].head;
	int index = -1, flag = 0;

	while (iterator) {
		int element = iterator->dest;
		index++;
		if (element == dest) {
			flag = 1;
			break;
		}
		iterator = iterator->next;
	}

	if (index == -1 || flag == 0) {
		printf("Edge is not present between [%d] and [%d].\n", src, dest);
		return;
	}
	if (index == 0) {
		g->array[src].head = iterator->next;
		g->E = g->E - 1;
		free(iterator);
		return;
	}
	int i;
	iterator = g->array[src].head;
	for (i = 0; i < index - 1; i++)
		iterator = iterator->next;
	AdjListNode* next = iterator->next->next;
	free(iterator->next);
	iterator->next = next;
	g->E = g->E - 1;

	return;
}

// A utility function to print the adjacency list representation of graph
void printGraph(Graph* graph)
{
	int v;

	for (v = 0; v < graph->V; ++v) {
		AdjListNode* pCrawl = graph->array[v].head;
		printf("[%d] ", v);
		while (pCrawl) {
			printf("-> [%d] (%lf)", pCrawl->dest, pCrawl->weight);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

int degreeVertex(Graph* g, int V)
{
	AdjListNode* iterator = g->array[V].head;
	int count = 0;

	while (iterator) {
		count++;
		iterator = iterator->next;
	}

	return count;
}

int* neighboursVertex(Graph* g, int V)
{
	int* neighbours = malloc(degreeVertex(g, V) * sizeof(int));

	AdjListNode* iterator = g->array[V].head;
	int i = 0;

	while (iterator) {
		neighbours[i] = iterator->dest;
		i++;
		iterator = iterator->next;
	}

	return neighbours;
}

// A utility function to create a new Min Heap Node
MinHeapNode* newMinHeapNode(int v, int dist)
{
	MinHeapNode* minHeapNode = malloc(sizeof(MinHeapNode));

	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

// A utility function to create a Min Heap
MinHeap* createMinHeap(int capacity)
{
	MinHeap* minHeap = malloc(sizeof(MinHeap));

	minHeap->pos = malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;

	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(MinHeap* minHeap, int idx)
{
	int smallest, left, right;

	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
	    minHeap->array[left]->dist < minHeap->array[smallest]->dist )
		smallest = left;

	if (right < minHeap->size &&
	    minHeap->array[right]->dist < minHeap->array[smallest]->dist )
		smallest = right;

	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode *smallestNode = minHeap->array[smallest];
		MinHeapNode *idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(MinHeap* minHeap)
{
	return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
MinHeapNode* extractMin(MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	MinHeapNode* root = minHeap->array[0];

	// Replace root node with last node
	MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(MinHeap* minHeap, int v, int dist)
{
	// Get the index of v in  heap array
	int i = minHeap->pos[v];

	// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(MinHeap *minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}

// A utility function used to print the solution
void printPath(double* dist, int dest)
{
	printf("Vertex   Distance from Source\n");
	if (dist[dest] != INFINITE)
		printf("%d \t\t %lf\n", dest, dist[dest]);
	else
		printf("%d \t\t INFINITY\n", dest);
}

// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
double* dijkstra(Graph* graph, int src)
{
	int V = graph->V;                               // Get the number of vertices in graph
	double* dist = malloc(V * sizeof(double));      // dist values used to pick minimum weight edge in cut

	// minHeap represents set E
	MinHeap* minHeap = createMinHeap(V);

	// Initialize min heap with all vertices. dist value of all vertices
	int v;

	for (v = 0; v < V; ++v) {
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	// Make dist value of src vertex as 0 so that it is extracted first
	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src]   = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the followin loop, min heap contains all nodes
	// whose shortest distance is not yet finalized.
	while (!isEmpty(minHeap)) {
		// Extract the vertex with minimum distance value
		MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their distance values
		AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL) {
			int v = pCrawl->dest;

			// If shortest distance to v is not finalized yet, and distance to v
			// through u is less than its previously calculated distance
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
			    pCrawl->weight + dist[u] < dist[v]) {
				dist[v] = dist[u] + pCrawl->weight;

				// update distance value in min heap also
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	// print the calculated shortest distances
	return dist;
}

void printArr(int arr[], int n)
{
	int i;
	for (i = 1; i < n; ++i)
		printf("%d --- %d\n", arr[i], i);
}

double* bellmanford(Graph* graph, int src)
{
	int V = graph->V;
	double* dist = malloc(V * sizeof(double));

	int i, j;

	// Setting Edges to INFINITY.
	for (i = 0; i < V; i++)
		dist[i] = INFINITE;
	dist[src] = 0;

	// Relaxing the edges.
	for (i = 0; i < V - 1; i++) {

		for (j = 0; j < V; j++) {
			AdjListNode* iterator = graph->array[j].head;
			while (iterator) {
				int u = j;
				int v = iterator->dest;
				double weight = iterator->weight;
				iterator = iterator->next;
				if (dist[u] != INFINITE
				    && dist[u] + weight < dist[v])
					dist[v] = dist[u] + weight;
			}
		}
	}

	for (i = 0; i < V; i++) {
		AdjListNode* iterator = graph->array[i].head;
		while (iterator) {
			int u = i;
			int v = iterator->dest;
			double weight = iterator->weight;
			iterator = iterator->next;

			if (dist[u] != INFINITE && dist[u] + weight < dist[v]) {
				printf("Graph contains negative weight cycle.\n");
				break;
			}
		}
	}
	return dist;
}

int DFS(Graph* g, int V, int* visited)
{
	visited[V] = 1;
	int num_neighbours = degreeVertex(g, V);
	int* neighbours = neighboursVertex(g, V);

	printf("[%d] got visited.\n", V);
	int i;
	for (i = 0; i < num_neighbours; i++)
		if (visited[neighbours[i]] == 0)
			DFS(g, neighbours[i], visited);
	return 0;
}

int do_DFS(Graph* g, int V)
{
	int* visited = calloc(g->V, sizeof(int));

	DFS(g, V, visited);
	return 0;
}

int do_BFS(Graph* g, int V)
{
	int* v = malloc(sizeof(int));

	*v = V;
	int* status = calloc(V, sizeof(int));

	GQueue* q = g_queue_new();
	g_queue_push_tail(q, v);

	status[*v] = 1;

	while (!(g_queue_is_empty(q))) {
		int v = *(int*)(g_queue_pop_head(q));
		printf("[%d] got visited.\n", v);
		status[v] = 2;
		int num_neighbours = degreeVertex(g, v);
		int* neighbours = neighboursVertex(g, v);

		int i;
		for (i = 0; i < num_neighbours; i++) {
			if (status[neighbours[i]] == 0) {
				g_queue_push_tail(q, &neighbours[i]);
				status[neighbours[i]] = 1;
			}
		}
	}
	return 0;
}

int MinDistance(double* distances, gboolean* processed, int size)
{
	int min = INFINITE;
	int minPosition;

	int i;

	for (i = 0; i < size; i++) {
		if (!processed[i] && distances[i] < min) {
			min = distances[i];
			minPosition = i;
		}
	}

	return minPosition;
}

Graph* primMST(Graph* graph, int source, int is_directed)
{
	AdjList* adjacency = graph->array;
	int numberOfNodes = graph->V;

	double* distances = malloc(numberOfNodes * sizeof(*distances));
	int* prev = malloc(numberOfNodes * sizeof(*prev));
	gboolean* processed = malloc(numberOfNodes * sizeof(*processed));
	int i;

	for (i = 0; i < numberOfNodes; i++) {
		distances[i] = INFINITE;
		processed[i] = FALSE;
		prev[i] = i;
	}
	distances[source] = 0;

	for (i = 0; i < numberOfNodes; i++) {
		int minVertex = MinDistance(distances, processed, numberOfNodes);
		processed[minVertex] = TRUE;

		AdjListNode* edgesIt = adjacency[minVertex].head;
		while (edgesIt != NULL) {
			AdjListNode* e = edgesIt;
			if (!processed[e->dest] && distances[e->dest] > e->weight) {
				distances[e->dest] = e->weight;
				prev[e->dest] = minVertex;
			}

			edgesIt = edgesIt->next;
		}
	}

	Graph* mst = createGraph(graph->V, is_directed);
	for (i = 0; i < graph->V; i++)
		if (i != prev[i])
			addEdge(mst, prev[i], i, distances[i]);

	return mst;
}

gint EdgeCompareFunction(gconstpointer a, gconstpointer b)
{
	DoubleEdge* aEdge = (DoubleEdge*)a;
	DoubleEdge* bEdge = (DoubleEdge*)b;

	return aEdge->weight > bEdge->weight;
}

Graph* KruskalMST(Graph* graph, int source, int is_directed)
{
	GSList* edges = NULL;
	int i;
	AdjListNode* edgesIt = NULL;

	for (i = 0; i < graph->V; i++) {
		edgesIt = graph->array[i].head;
		while (edgesIt != NULL) {
			AdjListNode* e = edgesIt;

			DoubleEdge* de = malloc(sizeof(*de));
			de->source = i;
			de->dest = e->dest;
			de->weight = e->weight;

			edges = g_slist_prepend(edges, de);

			edgesIt = edgesIt->next;
		}
	}

	edges = g_slist_sort(edges, &EdgeCompareFunction);

	Graph* mst = createGraph(graph->V, is_directed);
	int* sets = malloc(graph->V * sizeof(*sets));
	for (i = 0; i < graph->V; i++)
		sets[i] = i;

	int chosen = 0;
	while (edges != NULL && chosen < graph->V - 1) {
		DoubleEdge* e = (DoubleEdge*)edges->data;
		if (sets[e->source] != sets[e->dest]) {
			addEdge(mst, e->source, e->dest, e->weight);
			sets[e->dest] = sets[e->source];
			chosen++;
		}

		edges = g_slist_next(edges);
	}

	return mst;
}

#endif
