CC=gcc
CFLAGS=-g -Wall

all: lab9

lab9: lab9.c function.o
	$(CC) $(CFLAGS) lab9.c function.o -o lab9 -lm

function.o: function.c function.h
	$(CC) $(CFLAGS) function.c -c

clean:
	rm function.o lab9
