// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#include "bellman.h"

// Creates a graph with V vertices and E edges
Graph* new_graph(int V, int E)
{
	Graph* graph = malloc(sizeof(Graph));

	graph->V = V;
	graph->E = E;
	graph->edges = malloc(graph->E * sizeof(Edge));

	return graph;
}

double* find_bellmanford(Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	double* dist = malloc(V * sizeof(double));

	int i, j;

	// Setting Edges to INFINITY.
	for (i = 0; i < V; i++)
		dist[i] = INFINITE;
	dist[src] = 0;

	// Relaxing the edges.
	for (i = 0; i < V - 1; i++) {
		for (j = 0; j < E; j++) {
			int u = graph->edges[j].src;
			int v = graph->edges[j].dest;
			double weight = graph->edges[j].weight;
			if (dist[u] != INFINITE
			    && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	return dist;
}

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
		g->edges[i].src = src - 1;
		g->edges[i].dest = dest - 1;
		g->edges[i].weight = wt;
	}

	// Gets the source and number of destinations.
	fscanf(fp, "%d %lf", &g->src, &g->init_cond);

	fclose(fp);
	return g;
}
