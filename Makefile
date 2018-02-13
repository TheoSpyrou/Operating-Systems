CC=gcc
CFLAGS=-Wall

all: terminal
terminal: terminal.o
terminal.o: terminal.c

clean:
	rm -f terminal terminal.o
run:	terminal
	./terminal
