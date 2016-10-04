#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINTY INT_MAX

typedef struct _Edge {
	int src;
	int dest;
	int weight;
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
	if(g == NULL)
		return NULL;
	g->V = V;
	g->E = E;
	g->D = D;
	g->adj_mat = new_matrix(V, V);
	g->edges = malloc(E * sizeof(Edge));

	return g;
}
