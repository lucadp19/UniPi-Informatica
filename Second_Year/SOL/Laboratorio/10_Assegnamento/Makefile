CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs -lpthread
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : sigs/sigs sighandler

sighandler : server-sighandler/server server-sighandler/client

server-sighandler/% : server-sighandler/%.c libs/lib.o
	$(CC) $(CFLAGS) $< -o $@
	
sigs/sigs : sigs/sigs.c libs/lib.o
	$(CC) $(CFLAGS) $< -o $@

libs/lists.o : libs/lists.c libs/lib.h libs/lib.o 
	$(CC) $(CFLAGS) -c $< -o $@
	
libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
