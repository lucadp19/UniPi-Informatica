CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs -lpthread
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : mw1

mw2 : mw2/server mw2/client

mw2/server : mw2/server.c libs/lib.o libs/lists.o libs/hash.o
	$(CC) $(CFLAGS) $^ -o $@

mw2/client : mw2/client.c libs/lib.o libs/lists.o libs/hash.o
	$(CC) $(CFLAGS) $^ -o $@
	
mw1 : mw1/server mw1/client

mw1/server : mw1/server.c libs/lib.o libs/lists.o libs/hash.o
	$(CC) $(CFLAGS) $^ -o $@

mw1/client : mw1/client.c libs/lib.o libs/lists.o libs/hash.o
	$(CC) $(CFLAGS) $^ -o $@
	
libs/hash.o : libs/hash.c libs/hash.h libs/lib.o libs/lists.o
	$(CC) $(CFLAGS) -c $< -o $@

libs/lists.o : libs/lists.c libs/lib.h libs/lib.o 
	$(CC) $(CFLAGS) -c $< -o $@
	
libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
