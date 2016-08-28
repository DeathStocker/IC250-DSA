# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 3
# Make file inspired from my previous projects 'nako - Version Control, simplified.'
# and 'Simulation of the Solar System in C.'(ongoing)
# from https://github.com/DeathStocker

CC=gcc
CFLAGS=-c -Wall
LFLAGS=-Wall

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

# Source files in the project. Append new files here.
SRCS=queue_stack.c stack.c

# Create object files list from source files list.
OBJS= $(SRCS:.c=.o)

all: queue_stack
all: clean-objects

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) vel_ver

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

queue_stack: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o queue_stack

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
