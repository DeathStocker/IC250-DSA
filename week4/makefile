# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 4
# Make file inspired from my previous projects 'nako - Version Control, simplified.'
# and 'Simulation of the Solar System in C.'(ongoing)
# from https://github.com/DeathStocker

CC=gcc
CFLAGS=-c -Wall `pkg-config --cflags --libs glib-2.0`
LFLAGS=-Wall

GLIB=-lglib-2.0

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

# Source files in the project. Append new files here.
SRCS1=pal.c pal_func.c
SRCS2=reverse_stack.c reverse_stack_func.c stack.c
SRCS3=stack_queue.c stack_queue_func.c
SRCS4=fast_transpose.c fast_transpose_func.c

# Create object files list from source files list.
OBJS1= $(SRCS1:.c=.o)
OBJS2= $(SRCS2:.c=.o)
OBJS3= $(SRCS3:.c=.o)
OBJS4= $(SRCS4:.c=.o)

all: pal reverse_stack stack_queue fast_transpose

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) pal reverse_stack stack_queue

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

pal: $(OBJS1)
	$(CC) $(LFLAGS) $(OBJS1) -o pal $(GLIB)

reverse_stack: $(OBJS2)
	$(CC) $(LFLAGS) $(OBJS2) -o reverse_stack $(GLIB)

stack_queue: $(OBJS3)
	$(CC) $(LFLAGS) $(OBJS3) -o stack_queue $(GLIB)

fast_transpose: $(OBJS4)
	$(CC) $(LFLAGS) $(OBJS4) -o fast_transpose $(GLIB)

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
