// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY INT_MAX
#define clear() printf("\033[H\033[J")

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
	int** adj_mat;
	Edge* edges;
	int num;
	int* dests;
	int src;
} Graph;

int** new_matrix(int m, int n);
void free_matrix(int** arr, int m, int n);
Graph* new_graph(int V, int E);
int find_smallest_weight(int* dist, int* visited, int V);
Path* find_dijkstra(Graph* g, int src);
Graph* read_file();

#endif
