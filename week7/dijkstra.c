// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#include "dijkstra.h"

int main()
{
	Graph* g = read_file();

	Path* d = find_dijkstra(g, g->src - 1);
	int i;
	int count = 0;

	clear();
	for (i = 0; i < g->V; i++)
		if (g->dests[count] == i + 1) {
			if (d->dist[i] != INFINITY && d->dist[i] != INFINITY)
				printf("%d %d\n", g->dests[count], d->dist[i]);
			else
				printf("%d INFINITY\n", g->dests[count]);
			count++;
		}

	free(d->dist);
	free(d);
	free_matrix(g->adj_mat, g->V, g->V);
	free(g->edges);
	free(g->dests);
	free(g);
	return 0;
}
