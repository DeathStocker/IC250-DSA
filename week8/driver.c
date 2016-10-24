#include "graph.h"

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

	//BFS
	printf("\nBFS-\n");
	do_BFS(g, 0);

	// Prim MST
	printf("\nPrim MST - \n");
	Graph* prim_MST = primMST(g, 0, is_directed);
	printGraph(prim_MST);

	//Kruskal MST
	printf("\nKruskal MST - \n");
	Graph* kruskal_MST = KruskalMST(g, 0, is_directed);
	printGraph(kruskal_MST);

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
