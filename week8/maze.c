#include "graph.h"
#include <time.h>

Graph* generateMaze(int n)
{
	Graph* graph = createGraph(n * n, 0);
	int i, j, random;

	srand(time(NULL));
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n; j++) {
			if (j < n - 1) {
				random = rand() % 100;
				srand(random);
				int current_node = i * n + j;
				addEdge(graph, current_node, current_node + 1, random);
				random = rand() % 100;
				srand(random);
				addEdge(graph, current_node, current_node + n, random);
			} else {
				random = rand() % 100;
				srand(random);
				int current_node = i * n + j;
				addEdge(graph, current_node, current_node + n, random);
			}
		}
	}

	for (i = 0; i < n - 1; i++) {
		random = rand() % 100;
		srand(random);
		int current_node = (n - 1) * n + i;
		addEdge(graph, current_node, current_node + 1, random);
	}

	return graph;
}

int getRandSrc(int n)
{
	srand(time(NULL));
	return rand() % (n * n);
}

int getRandDest(int n, int src)
{
	srand(time(NULL));
	int dest = src;
	while (dest == src) {
		int random = rand();
		srand(random);
		dest = random % (n * n);
	}

	return dest;
}

void printMazePath(int* predecessor, int src, int dest)
{
	int iterator = dest;
	GSList* list = NULL;

	do {
		int* v = malloc(sizeof(int));
		*v = iterator;
		list = g_slist_prepend(list, v);
		iterator = predecessor[iterator];
	} while (iterator != src && iterator != -1);
	int* v = malloc(sizeof(int));
	*v = src;
	list = g_slist_prepend(list, v);

	GSList* iter = list;
	while (iter) {
		printf("%d->", *(int*)(iter->data));
		iter = iter->next;
	}
	printf("STOP.\n");
}

int** matrixifyAdjList(Graph* g)
{
	int** arr = calloc(g->V, sizeof(int*));
	int i;

	for (i = 0; i < g->V; i++)
		arr[i] = calloc(g->V, sizeof(int));
	int v;
	for (v = 0; v < g->V; ++v) {
		AdjListNode* pCrawl = g->array[v].head;
		// printf("[%d] ", v);
		while (pCrawl) {
			if (pCrawl->weight == 0)
				pCrawl->weight = 1;
			arr[v][pCrawl->dest] = (int)(pCrawl->weight);
			// printf("-> [%d] (%lf)", pCrawl->dest, pCrawl->weight);
			pCrawl = pCrawl->next;
		}
	}

	return arr;
}

void printMatrix(int** arr, int m, int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Enter the side of the square maze.\n");
		return 1;
	}
	clear();
	int num = atoi(argv[1]);

	Graph* g = generateMaze(num);

	int src = getRandSrc(num);
	int dest = getRandDest(num, src);

	// Creates the maze paths from source to destination.
	Graph* prim_MST = primMST(g, src, 0);

	// Printing
	printf("Matrix Representation -\n");
	int** arr = matrixifyAdjList(prim_MST);
	printMatrix(arr, g->V, g->V);
	printf("\n\nList Representation - \n");
	printGraph(prim_MST);

	// Gives shortest path to all vertices from source.
	dijk* path = dijkstra(prim_MST, src);
	printf("\n\nSource = %d Destination = %d\n", src, dest);

	// Prints the maze path from src to dest including the vertices in between.
	printf("\nPath from [%d] to [%d] - \n\n", src, dest);
	printMazePath(path->predecessor, src, dest);

	return 0;
}
