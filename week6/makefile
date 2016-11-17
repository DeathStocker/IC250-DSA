# Name - Utkarsh Kunwar
# Roll No. - B15338
# IC-250 Week - 6
# Make file inspired from my previous projects 'nako - Version Control, simplified.'
# and 'Simulation of the Solar System in C.'(ongoing)
# from https://github.com/DeathStocker

CC=gcc
CFLAGS=-c -Wall
LFLAGS=-Wall

#GLIB=-lglib-2.0

DFLAGS=-g -Wextra -Werror

RM=rm
RMFLAGS=-f

# Source files in the project. Append new files here.
SRCS1=a.c a_func.c
SRCS2=b.c b_func.c
SRCS3=c.c c_func.c

# Create object files list from source files list.
OBJS1= $(SRCS1:.c=.o)
OBJS2= $(SRCS2:.c=.o)
OBJS3= $(SRCS3:.c=.o)

all: a b c

# Clean completely wipes the directory of all executables and objects
clean: clean-objects
	$(RM) $(RMFLAGS) a b c

# Only removes objects, not the final executable
clean-objects:
	$(RM) $(RMFLAGS) *.o

debug: CFLAGS+=$(DFLAGS)
debug: LFLAGS+=$(DFLAGS)
debug: all

a: $(OBJS1)
	$(CC) $(LFLAGS) $(OBJS1) -o a

b: $(OBJS2)
	$(CC) $(LFLAGS) $(OBJS2) -o b

c: $(OBJS3)
	$(CC) $(LFLAGS) $(OBJS3) -o c

# The following magic code is from here:
# http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# Use with care. This automatically builds all .c files inside the folder.
.c.o:
	$(CC) $(CFLAGS) $< -o $@
