CFLAGS=-Wall -g
HEADERS=utils.h

default: solchess

solchess: solchess.o
	gcc solchess.c utils.c -lm -o solchess

clean:
	rm -f solchess
	rm -f solchess.o
