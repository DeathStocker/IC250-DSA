// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#include "dijkstra.h"

int** new_matrix(int m, int n)
{
	int i;
	int** arr = calloc(m, sizeof(int*));

	if (arr == NULL)
		return NULL;

	for (i = 0; i < n; i++)
		arr[i] = calloc(n, sizeof(int));
	return arr;
}

void free_matrix(int** arr, int m, int n)
{
	(void)m;
	int i;
	for(i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

Graph* new_graph(int V, int E)
{
	Graph* g = malloc(sizeof(Graph));

	if (g == NULL)
		return NULL;
	g->V = V;
	g->E = E;
	g->adj_mat = new_matrix(V, V);
	g->edges = malloc(E * sizeof(Edge));

	return g;
}

int find_smallest_weight(int* dist, int* visited, int V)
{
	int min = INFINITY;
	int index = INFINITY;

	int i;

	for (i = 0; i < V; i++) {
		if (visited[i] == 0 && dist[i] <= min) {
			min = dist[i];
			index = i;
		}
	}

	return index;
}

Path* find_dijkstra(Graph* g, int src)
{
	Path* dijk = malloc(sizeof(Path));

	if (dijk == NULL)
		return NULL;
	dijk->dist = malloc((g->V) * sizeof(int));
	dijk->v = g->V;

	int** adj_mat = g->adj_mat;
	if (adj_mat == NULL)
		return NULL;

	int v = g->V;
	int dist[v];
	int visited[v];

	int i;
	for (i = 0; i < v; i++) {
		dist[i] = INFINITY;
		visited[i] = 0;
	}
	dist[src] = 0;

	for (i = 0; i < v - 1; i++) {
		int u = find_smallest_weight(dist, visited, v);
		if (u == INFINITY)
			continue;
		visited[u] = 1;
		int j;
		for (j = 0; j < v; j++)
			if (visited[j] == 0 && adj_mat[u][j] && (dist[u] + adj_mat[u][j]) < dist[j])
				dist[j] = dist[u] + adj_mat[u][j];

	}

	for (i = 0; i < v; i++)
		dijk->dist[i] = dist[i];

	return dijk;
}

// Reads the graph from the file.
Graph* read_file()
{
	printf("Enter the file name to load = ");
	char filename[256];
	scanf("%s", filename);
	FILE* fp = fopen(filename, "r");

	// Error Checking
	if (fp == NULL) {
		printf("Cannot open file \"%s\".", filename);
		return NULL;
	}

	// Number of Vertices and Edges.
	int V, E;
	fscanf(fp, "%d %d", &V, &E);

	Graph* g = new_graph(V, E);

	// Initialises the values to the graph.
	int i;
	for (i = 0; i < E; i++) {
		int src, dest;
		double wt;
		fscanf(fp, "%d %d %lf", &src, &dest, &wt);
		g->edges[i].src = src;
		g->edges[i].dest = dest;
		g->edges[i].weight = wt;
		g->adj_mat[src - 1][dest - 1] = wt;
	}

	// Gets the source and number of destinations.
	fscanf(fp, "%d %d", &g->src, &g->num);

	g->dests = malloc((g->num) * sizeof(int));
	for (i = 0; i < g->num; i++)
		fscanf(fp, "%d", &g->dests[i]);

	fclose(fp);
	return g;
}
