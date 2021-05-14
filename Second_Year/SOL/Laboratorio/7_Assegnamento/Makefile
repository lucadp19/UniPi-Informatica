CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs -lpthread
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : P-C/prod-cons

P-C/prod-cons : P-C/prod-cons.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
