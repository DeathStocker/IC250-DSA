// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#ifndef BELLMAN_H
#define BELLMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define INFINITE INT_MAX
#define clear() printf("\033[H\033[J")

typedef struct _Edge {
	int src;
	int dest;
	double weight;
} Edge;

typedef struct _Graph {
	int V;
	int E;
	int** adj_mat;
	Edge* edges;
	int num;
	int* dests;
	int src;
	double init_cond;
} Graph;

Graph* new_graph(int V, int E);
double* find_bellmanford(Graph* graph, int src);
Graph* read_file();

#endif
