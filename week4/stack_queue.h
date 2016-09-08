/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include "queue.h"

int* popStack_Queue(GQueue* src, GQueue* dest);

int transfer_queue(GQueue* src, GQueue* dest);

int process_queue(GQueue* stack, GQueue* temp, int ch);

int input(GQueue* stack, GQueue* temp);

#endif
