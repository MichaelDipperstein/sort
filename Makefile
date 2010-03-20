# Makefile for sort
CC = gcc
LD = gcc
CFLAGS = -O2 -Wall -Wextra -pedantic -ansi -c
LDFLAGS = -O2 -o
OBJS = sample.o sort.o

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

sample$(EXE):	$(OBJS)
		$(LD) $^ $(LDFLAGS) $@

sample.o:	sample.c sort.h
		$(CC) $(CFLAGS) $<

sort.o:		sort.c sort.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) sample$(EXE)
