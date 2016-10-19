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

int readFile(char* filename)
{
	clear();
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File cannot be opened.\n");
		return 1;
	}
	int v, e, is_directed;
	fscanf(fp, "%d %d %d", &is_directed, &v, &e);
	Graph* g = createGraph(v, is_directed);

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
	//dijkstra
	printGraph(g);
	printf("Num edges = %d\n", g->E);
	double* dist = dijkstra(g, 1);
	printPath(dist, 3);

	// Degree
	printf("Degree of [1] = %d\n\n", degreeVertex(g, 1));

	// Neighbours
	int* neigh = neighboursVertex(g, 1);
	printf("Neighbours of [1] = ");
	for (i = 0; i < degreeVertex(g, 1); i++)
		printf("%d ", neigh[i]);
	printf("\n\n");

	// Deleting Edge.
	deleteEdge(g, 3, 4);
	printGraph(g);

	// Adding Edge.
	addEdge(g, 4, 3, 3);
	printGraph(g);

	// Bellmanford
	dist = bellmanford(g, 1);
	printPath(dist, 3);

	// DFS
	printf("\nDFS-\n");
	do_DFS(g, 0);

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
