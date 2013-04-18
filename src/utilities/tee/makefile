#makefile for tee

OBJS = tee.o
CC = gcc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

tee : $(OBJS)
	$(CC) $(OBJS) -o tee
	strip --strip-unneeded tee
	
tee.o : tee.c
	$(CC) $(CFLAGS) $(SPATH) tee.c

clean:
	\rm *.o tee
