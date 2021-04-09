CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I ./libs
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : cp/cp_stdio cp/cp_syscall

cp/cp_syscall : cp/cp_syscall.c libs/lib.o 
	$(CC) $(CFLAGS) $^ -o $@

cp/cp_stdio : cp/cp_stdio.c libs/lib.o
	$(CC) $(CFLAGS) $^ -o $@

libs/lib.o : libs/lib.c libs/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f libs/lib.o
