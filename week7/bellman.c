// Name - Utkarsh Kunwar
// Roll No. - B15338
// IC-250 Week - 7

#include "bellman.h"

int main()
{
	Graph* g = read_file();

	double* dist = find_bellmanford(g, g->src - 1);

	clear();
	double least_weight = INFINITE;
	int planet_least_weight = 0;
	int i;

	// Finding the least weight.
	for (i = 0; i < g->V; i++) {
		// printf("%d %lf\n", i + 1, dist[i]);
		if (dist[i] < least_weight) {
			least_weight = dist[i];
			planet_least_weight = i + 1;
		}
	}

	least_weight = g->init_cond * pow(10, least_weight);
	printf("%d %lf\n", planet_least_weight, least_weight);

	free(g->edges);
	free(g);
	free(dist);
	return 0;
}
