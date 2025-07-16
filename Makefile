INCDIR  = include
SRCDIR  = src
LIBDIR  = lib

OBJ     = $(SRCDIR)/scalar.o $(SRCDIR)/vector.o $(SRCDIR)/matrix.o
LIB     = $(LIBDIR)/libkgt.a

CC      = gcc
CFLAGS  = -O2 -march=native -Wall -Wextra -Wshadow -I$(INCDIR)

.PHONY: all clean format

all:    $(LIB)

clean:
	rm -f $(OBJ) $(LIB)

format:
	clang-format -i $(INCDIR)/*.h $(SRCDIR)/*.c

$(LIB): $(OBJ)
	rm -f $(LIB)
	ar cr $(LIB) $(OBJ)
	ranlib $(LIB)
