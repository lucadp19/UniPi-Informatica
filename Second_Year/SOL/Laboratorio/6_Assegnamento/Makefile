CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : 2_Es/background 3_Es/zombie 4_Es/family 

2_Es/background : 2_Es/background.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

3_Es/zombie : 3_Es/zombie.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

4_Es/family : 4_Es/family.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
