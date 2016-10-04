#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINTY INT_MAX

typedef struct _Edge {
	int src;
	int dest;
	double weight;
} Edge;

typedef struct _Path {
	int v;
	int* dist;
} Path;

typedef struct _Graph {
	int V;
	int E;
	int D;
	int** adj_mat;
	Edge* edges;
} Graph;

int** new_matrix(int m, int n)
{
	int i;
	int** arr = malloc(m * sizeof(int*));

	if (arr == NULL) {
		free(arr);
		return NULL;
	}

	for (i = 0; i < n; i++) {
		arr[i] = malloc(n * sizeof(int));
		if (arr[i] == NULL) {
			int j;
			for (j = i; j >= 0; j--)
				free(arr[j]);
			free(arr);
			return NULL;
		}
	}
	return arr;
}

Graph* new_graph(int V, int E, int D)
{
	Graph* g = malloc(sizeof(Graph));

	if (g == NULL)
		return NULL;
	g->V = V;
	g->E = E;
	g->D = D;
	g->adj_mat = new_matrix(V, V);
	g->edges = malloc(E * sizeof(Edge));

	return g;
}

int smallest_weight(int* dist, int* visited, int V)
{
	int min = INFINTY;
	int index = INFINTY;

	int i;

	for (i = 0; i < V; i++) {
		if (visited[i] == 0 && dist[i] <= min) {
			min = dist[i];
			index = i;
		}
	}

	return index;
}

int read_file()
{
	printf("Enter the file name to load = ");
	char filename[256];
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Cannot open file \"%s\".", filename);
		return 1;
	}

	int V, E;
	fscanf(fp, "%d %d", &V, &E);

	Graph* g = new_graph(V, E, 0);

	int i;
	for (i = 0; i < E; i++) {
		int src, dest;
		double wt;
		fscanf(fp, "%d %d %lf", &src, &dest, &wt);
		g->edges[i].src = src;
		g->edges[i].dest = dest;
		g->edges[i].weight = wt;
	}

	int src;
	double wt;
	fscanf(fp, "%d %lf", &src, &wt);

	return 0;
}

int main()
{
	read_file();

	return 0;
}
