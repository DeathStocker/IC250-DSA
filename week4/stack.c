#include "stack.h"


Stack* stack_new()
{
	Stack *stack;

	stack = g_slice_alloc(sizeof *stack);
	stack->head = NULL;

	return stack;
}

void stack_free(Stack *stack, GFreeFunc free_func)
{
	while (stack->head) {
		GSList *next = stack->head->next;

		if (free_func)
			free_func(stack->head->data);
		g_slist_free_1(stack->head);
		stack->head = next;
	}
	g_slice_free1(sizeof *stack, stack);
}

void stack_push(Stack *stack, gpointer data)
{
	stack->head = g_slist_prepend(stack->head, data);
}

gpointer stack_pop(Stack *stack)
{
	gpointer data = NULL;

	if (stack->head) {
		GSList *next = stack->head->next;

		data = stack->head->data;
		g_slist_free_1(stack->head);
		stack->head = next;
	}

	return data;
}

gpointer stack_peek(const Stack *stack)
{
	return (stack->head) ? stack->head->data : NULL;
}

int is_empty(const Stack *stack)
{
	return stack->head == NULL;
}
