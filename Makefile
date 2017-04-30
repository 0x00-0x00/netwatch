CC=gcc
CFLAGS=-std=gnu99 -Wall
PROG=nwc
nwc: src/nwc.c
	$(CC) -o $(PROG) src/nwc.c $(CFLAGS)


