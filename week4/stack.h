/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>


typedef struct _Stack {
	GSList* head;
} Stack;

Stack* stack_new();

void stack_free(Stack *stack, GFreeFunc free_func);

void stack_push(Stack *stack, gpointer data);

gpointer stack_pop(Stack *stack);

gpointer stack_peek(const Stack *stack);

gboolean is_empty(const Stack *stack);

#endif
