#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <glib.h>
#include <stdlib.h>

#define newQueue g_queue_new
#define isQueueEmpty g_queue_is_empty
#define getQueueLength g_queue_get_length
#define pushQueue g_queue_push_tail
#define popQueue g_queue_pop_head
#define peekQueue g_queue_peek_tail
#define reverseQueue g_queue_reverse
#define copyQueue g_queue_copy
#define clear() printf("\033[H\033[J")

#endif
