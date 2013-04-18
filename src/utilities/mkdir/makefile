#makefile fo mkdir

OBJS = mkdir.o bitsmode.o pathl.o
CC = gcc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

mkdir : $(OBJS)
	$(CC) $(OBJS) -o mkdir
	strip --strip-unneeded mkdir
	
mkdir.o : mkdir.c ../../lib/bitsmode.h ../../lib/pathl.h
	$(CC) $(CFLAGS) $(SPATH) mkdir.c
	
bitsmode.o : ../../lib/bitsmode.c ../../lib/bitsmode.h
	$(CC) $(CFLAGS) ../../lib/bitsmode.c
	
pathl.o : ../../lib/pathl.c ../../lib/pathl.h
	$(CC) $(CFLAGS) ../../lib/pathl.c
	
clean:
	\rm *.o mkdir
