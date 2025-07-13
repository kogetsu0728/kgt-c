INCDIR  = include
SRCDIR  = src
LIBDIR  = lib

OBJ     = $(SRCDIR)/vector.o $(SRCDIR)/matrix.o
LIB     = $(LIBDIR)/libkgt.a

CC      = gcc
CFLAGS  = -O2 -march=native -Wall -Wextra -Wshadow -I$(INCDIR)

.PHONY: all clean

all:    $(LIB)

clean:
	rm -f $(LIB) $(OBJ)

$(LIB): $(OBJ)
	rm -f $(LIB)
	ar cr $(LIB) $(OBJ)
	ranlib $(LIB)
