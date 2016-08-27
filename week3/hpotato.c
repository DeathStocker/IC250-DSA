#include <stdio.h>
#include <glib.h>

#define G_QUEUE_INIT { NULL, NULL, 0 }

int main()
{
	int n, i;

	printf("Please enter the values of n and i : ");
	scanf("%d %d", &n, &i);

	GQueue* children = g_queue_new();

	int i;
	for(i = 1; i <= n; i++)
	{
		g_queue_push_tail(children, i);
	}

	printf("\nThe removal sequence is as follows - \n\n");

	return 0;
}
