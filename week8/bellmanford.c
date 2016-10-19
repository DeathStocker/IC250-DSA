#include "bellmanford.h"

double* bellmanford(Graph* graph, int src)
{
	int V = graph->V;
	double* dist = malloc(V * sizeof(double));

	int i, j;

	// Setting Edges to INFINITY.
	for (i = 0; i < V; i++)
		dist[i] = INFINITE;
	dist[src] = 0;

	// Relaxing the edges.
	for (i = 0; i < V - 1; i++) {

		for (j = 0; j < V; j++) {
			AdjListNode* iterator = graph->array[j].head;
			while (iterator) {
				int u = j;
				int v = iterator->dest;
				double weight = iterator->weight;
				iterator = iterator->next;
				if (dist[u] != INFINITE
				    && dist[u] + weight < dist[v])
					dist[v] = dist[u] + weight;
			}
		}
	}

	for (i = 0; i < V; i++) {
		AdjListNode* iterator = graph->array[i].head;
		while (iterator) {
			int u = i;
			int v = iterator->dest;
			double weight = iterator->weight;
			iterator = iterator->next;

			if (dist[u] != INFINITE && dist[u] + weight < dist[v]) {
				printf("Graph contains negative weight cycle.\n");
				break;
			}
		}
	}
	return dist;
}
