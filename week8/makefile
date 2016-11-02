# Name - Utkarsh Kunwar
# Roll No. - B15338
# Week - 8
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
SRCS1=driver.c
SRCS2=maze.c

# Create object files list from source files list.
OBJS1= $(SRCS1:.c=.o)
OBJS2= $(SRCS2:.c=.o)

all: driver maze

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) driver maze

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

driver: $(OBJS1)
	$(CC) $(LFLAGS) $(OBJS1) -o driver $(GLIB)

maze: $(OBJS2)
	$(CC) $(LFLAGS) $(OBJS2) -o maze $(GLIB)

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
