#makefile for chmod

OBJS = chmod.o bitsmode.o
CC = cc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

chmod : $(OBJS)
	$(CC) $(OBJS) -o chmod
	strip --strip-unneeded chmod

chmod.o : chmod.c ../../lib/bitsmode.h
	$(CC) $(CFLAGS) $(SPATH) chmod.c

bitsmode.o : ../../lib/bitsmode.c ../../lib/bitsmode.h
	$(CC) $(CFLAGS) ../../lib/bitsmode.c

clean:
	\rm *.o chmod
