OBJ    = vector.o matrix.o
LIB    = ../lib/libkgt.a

CC     = gcc
CFLAGS = -O2 -march=native -Wall -Wextra -Wshadow -I../include

.PHONY: all clean

all: $(LIB)

clean:
	rm -f $(LIB) $(OBJ)

$(LIB): $(OBJ)
	rm -f $(LIB)
	ar cr $(LIB) $(OBJ)
	ranlib $(LIB)
