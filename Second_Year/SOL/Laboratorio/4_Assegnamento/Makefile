CC			=  gcc
CFLAGS	    += -Wall -pedantic -g -I "../Utils"
# TARGETS		= 

.PHONY: clean
.SUFFIXES: .c .h

all : Wc/wc Mats/read_mats Mats/write_mats Passwd/passwd

Wc/wc : Wc/wc.c Utils/utils.o
	$(CC) $(CFLAGS) $^ -o $@

Mats/read_mats : Mats/read_mats.c Utils/utils.o 
	$(CC) $(CFLAGS) $^ -o $@

Mats/write_mats : Mats/write_mats.c Utils/utils.o 
	$(CC) $(CFLAGS) $^ -o $@

Passwd/passwd : Passwd/passwd.c Utils/utils.o
	$(CC) $(CFLAGS) $^ -o $@

Utils/utils.o : Utils/utils.c Utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	-rm -f Utils/utils.o