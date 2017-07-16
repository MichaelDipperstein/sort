# Makefile for sort
CC = gcc
LD = gcc
CFLAGS = -O2 -Wall -Wextra -pedantic -ansi -c
LDFLAGS = -O2 -o

# libraries
LIBS = -L optlist -loptlist

# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm
endif

all:		sample$(EXE)

sample$(EXE):	sample.o sort.o optlist/liboptlist.a
		$(LD) $^ $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c sort.h  optlist/optlist.h
		$(CC) $(CFLAGS) $<

sort.o:		sort.c sort.h
		$(CC) $(CFLAGS) $<

optlist/liboptlist.a:
		cd optlist && $(MAKE) liboptlist.a

clean:
		$(DEL) *.o
		$(DEL) sample$(EXE)
		cd optlist && $(MAKE) clean
