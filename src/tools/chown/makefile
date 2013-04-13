#makefile for chown

OBJS = chown.o
CC = gcc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

chown : $(OBJS)
	$(CC) $(OBJS) -o chown
	strip --strip-unneeded chown

chown.o : chown.c
	$(CC) $(CFLAGS) $(SPATH) chown.c

clean:
	\rm *.o chown
