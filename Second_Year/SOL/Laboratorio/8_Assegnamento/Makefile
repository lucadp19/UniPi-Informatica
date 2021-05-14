CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs -lpthread
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : Calc/calc ProdCons2/prodcons

ProdCons2/prodcons : ProdCons2/prodcons.c libs/lib.o libs/lists.o
	$(CC) $(CFLAGS) $^ -o $@

Calc/calc : Calc/calc.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

libs/lists.o : libs/lists.c libs/lib.h libs/lib.o 
	$(CC) $(CFLAGS) -c $< -o $@
	
libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
