#makefile for tail

OBJS = tail.o
CC = gcc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

tail : $(OBJS)
	$(CC) $(OBJS) -o tail
	
tail.o : tail.c
	$(CC) $(CFLAGS) $(SPATH) tail.c

clean:
	\rm *.o tail
