CC = gcc
CCFLAGS = -Wall

all: memgrind

memgrind: memgrind.c mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -g -lm -std=c99 -o memgrind memgrind.c

clean:
	rm memgrind
