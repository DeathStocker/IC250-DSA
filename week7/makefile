# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 7
# Make file inspired from my previous projects 'nako - Version Control, simplified.'
# and 'Simulation of the Solar System in C.'(ongoing)
# from https://github.com/DeathStocker

CC=gcc
LFLAGS=-Wall

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

all: dijkstra bellman

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) dijkstra bellman

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

dijkstra: $(OBJS1)
	$(CC) $(LFLAGS) dijkstra.c dijkstra_func.c -o dijkstra -lm

bellman:
	$(CC) $(LFLAGS) bellman.c bellman_func.c -o bellman -lm

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
