#ifndef PAL_H
#define PAL_H

#include "stack.h"

GSList* stackify(char* s, int length);

char* rev_string(GSList* str, int length);

#endif
