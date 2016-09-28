# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 5
# Make file inspired from my previous projects 'nako - Version Control, simplified.'
# and 'Simulation of the Solar System in C.'(ongoing)
# from https://github.com/DeathStocker

CC=gcc
CFLAGS=-c -Wall
LFLAGS=-Wall

DFLAGS=-g -Wextra -Werror

ENDFLAGS=-lm

RM=rm
RMFLAGS=-f

# Source files in the project. Append new files here.
SRCS1=mech_ass.c mech_ass_func.c

# Create object files list from source files list.
OBJS1= $(SRCS1:.c=.o)

all: mech_ass

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) mech_ass

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

mech_ass: $(OBJS1)
	$(CC) $(LFLAGS) $(OBJS1) -o mech_ass $(ENDFLAGS)

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
