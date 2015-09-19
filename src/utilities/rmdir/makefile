#makefile for rmdir

OBJS = rmdir.o pathr.o
CC = cc
DEBUG = -O3
CFLAGS = -c $(DEBUG)
SPATH = -I../../lib/

rmdir : $(OBJS)
	$(CC) $(OBJS) -o rmdir
	strip --strip-unneeded rmdir

rmdir.o : rmdir.c ../../lib/pathl.h
	$(CC) $(CFLAGS) $(SPATH) rmdir.c

pathr.o : ../../lib/pathr.c ../../lib/pathr.h
	$(CC) $(CFLAGS) ../../lib/pathr.c

clean:
	\rm *.o rmdir
