CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs -lpthread
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : bc to_upper

to_upper : to_upper/client to_upper/server

bc : bc/client bc/server

to_upper/% : to_upper/%.c libs/lib.o
	$(CC) $(CFLAGS) $^ -o $@

bc/% : bc/%.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

libs/lists.o : libs/lists.c libs/lib.h libs/lib.o 
	$(CC) $(CFLAGS) -c $< -o $@
	
libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
