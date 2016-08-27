/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void display(int count, int pos, int num_child, int iter)
{
	if(count == iter)
		printf("[%d] Firstly, the person at position %d "
		"is removed.\n", (count/iter), pos);
	else if (count == iter * (num_child - 1))
		printf("[%d] Finally, the person at position %d "
		"is removed.\n", (count/iter), pos);
	else
		printf("[%d] Then, the person at position %d "
		"is removed.\n", (count/iter), pos);

}

int passThePotato(GQueue* children, int n, int iter)
{
	int c = 1;
	while(g_queue_get_length(children) > 1) {
		// int i;
		int *val;
		val = malloc(sizeof(*val));

		val = (int*)(g_queue_pop_head(children));

		if(c % iter != 0)
			g_queue_push_tail(children, val);
		else
			display(c, *val, n, iter);
		c++;
	}

	int winner = *(int*)(g_queue_pop_head(children));

	return winner;
}

int main()
{
	int n, iter;

	printf("Please enter the values of n and i : ");
	scanf("%d %d", &n, &iter);

	GQueue* children = g_queue_new();

	int* val;

	int i;
	for(i = 0; i < n; i++)
	{
		val = malloc(sizeof(*val));
		*val = i + 1;
		g_queue_push_tail(children, val);
	}

	printf("\nThe removal sequence is as follows -\n\n");

	int winner = passThePotato(children, n, iter);

	// printf("\nThe removal sequence is as follows - \n\n");
	printf("\nHence, the person at position %d survives.\n", winner);

	g_queue_free(children);
	free(val);

	return 0;
}
