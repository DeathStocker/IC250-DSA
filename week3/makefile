# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 3
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
SRCS1=hpotato.c
SRCS2=queue_stack.c stack.c

# Create object files list from source files list.
OBJS1= $(SRCS1:.c=.o)
OBJS2= $(SRCS2:.c=.o)

all: queue_stack hpotato

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) queue_stack hpotato

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

hpotato: $(OBJS1)
	$(CC) $(LFLAGS) $(OBJS1) -o hpotato $(GLIB)
	make clean-objects

queue_stack: $(OBJS2)
	$(CC) $(LFLAGS) $(OBJS2) -o queue_stack
	make clean-objects

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
