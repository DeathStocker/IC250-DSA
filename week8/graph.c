#include "graph.h"

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
