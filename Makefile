# Makefile for sort
CC = gcc
LD = gcc
CFLAGS = -O2 -Wall -Wextra -pedantic -ansi -c
C99FLAGS = -O2 -Wall -Wextra -std=c99 -c
LDFLAGS = -O2 -o

# libraries
LIBS = -L. -loptlist

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

all:		sample$(EXE) sample64$(EXE)

sample$(EXE):	sample.o sort.o liboptlist.a
		$(LD) $^ $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c sort.h optlist.h
		$(CC) $(CFLAGS) $<

sample64$(EXE):	sample64.o sort.o mwc.o liboptlist.a
		$(LD) $^ $(LIBS) $(LDFLAGS) $@

sample64.o:	sample64.c sort.h optlist.h mwc.h
		$(CC) $(C99FLAGS) $<

sort.o:		sort.c sort.h
		$(CC) $(CFLAGS) $<

mwc.o:		mwc.c mwc.h
		$(CC) $(C99FLAGS) $<


liboptlist.a:	optlist.o
		ar crv liboptlist.a optlist.o
		ranlib liboptlist.a

optlist.o:	optlist.c optlist.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) *.a
		$(DEL) sample$(EXE)
		$(DEL) sample64$(EXE)
