#######################################################################
#Description  Makefile
#Authors      Varun Vijaykumar
#Date 	      27 May 2015
########################################################################
CC = gcc
HEADERS = TDA.h
SOURCES= TDA.c
CFLAGS = -std=c99 -Wall -lm -o

bin = schedulability

$(bin) : $(HEADERS) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $@

clean:
	rm -vrf $(bin)
