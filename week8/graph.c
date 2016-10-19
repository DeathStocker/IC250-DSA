#include "graph.h"
#include "dijkstra.h"
#include "bellmanford.h"

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
Graph* createGraph(int V, int E)
{
	Graph* graph = malloc(sizeof(Graph));

	graph->V = V;
	graph->E = E;

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

	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

Graph* deleteEdge(Graph* g, int src, int dest)
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
		return g;
	}
	if(index == 0) {
		g->array[src].head = iterator->next;
		free(iterator);
		return g;
	}
	int i;
	iterator = g->array[src].head;
	for (i = 0; i < index - 1; i++)
		iterator = iterator->next;
	AdjListNode* next = iterator->next->next;
	free(iterator->next);
	iterator->next = next;

	return g;
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

int readFile(char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File cannot be opened.\n");
		return 1;
	}
	int v, e;
	fscanf(fp, "%d %d", &v, &e);
	Graph* g = createGraph(v, e);

	int i;
	for (i = 0; i <= e; i++) {
		int src, dest;
		double wt;
		int count = fscanf(fp, "%d %d %lf", &src, &dest, &wt);
		if (i < e)
			addEdge(g, src, dest, wt);
		if (count != 3 && i != e) {
			printf("Number of edges is less than that specified.\n");
			return 1;
		} else if (count == 3 && i == e) {
			printf("Number of edges is more than that specified.\n");
			return 1;
		}
	}

	// Testing
	printGraph(g);
	double* dist = dijkstra(g, 1);
	printPath(dist, 3);

	printf("Degree of [1] = %d\n\n", degreeVertex(g, 1));

	int* neigh = neighboursVertex(g, 1);
	printf("Neighbours of [1] = ");
	for (i = 0; i < degreeVertex(g, 1); i++)
		printf("%d ", neigh[i]);
	printf("\n\n");

	g = deleteEdge(g, 1, 3);
	printGraph(g);

	return 0;
}

// Driver program to test above functions
int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Enter 1 filename.\n");
		return 1;
	}

	readFile(argv[1]);

	return 0;
}
