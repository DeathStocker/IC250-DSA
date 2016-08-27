#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int passThePotato(GQueue* children, int iter)
{
	int c = 1;
	while(g_queue_get_length(children) > 1) {
		// int i;
		int *arr;

		arr = malloc(sizeof(*arr));
		arr = (int*)(g_queue_pop_head(children));
		if(c % iter != 0)
			g_queue_push_tail(children, arr);
		else
			printf("%d got eliminated.\n", *arr);
		c++;
		// for(i = 0; i < iter - 1; i++) {
		//
		// }

	}

	printf("winner should be = %d\n", *(int*)(children->head->data));

	int winner = *(int*)(g_queue_pop_head(children));

	return winner;
}

int main()
{
	int n, iter;

	printf("Please enter the values of n and i : ");
	scanf("%d %d", &n, &iter);

	GQueue* children = g_queue_new();

	int* arr;

	int i;
	for(i = 0; i < n; i++)
	{
		arr = malloc(sizeof(*arr));
		*arr = i + 1;
		g_queue_push_tail(children, arr);
	}

	int winner = passThePotato(children, iter);

	// printf("\nThe removal sequence is as follows - \n\n");
	printf("But the Winner = %d\n", winner);

	g_queue_free(children);
	free(arr);

	return 0;
}
