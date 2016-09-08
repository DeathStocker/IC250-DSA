/*
   Name - Utkarsh Kunwar
   Roll No. - B15338
   IC-250 Week - 4
 */

#ifndef PAL_H
#define PAL_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

GSList* stackify(char* s, int length);

char* rev_string(GSList* str, int length);

#endif
