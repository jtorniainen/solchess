CFLAGS=-Wall -g
HEADERS=utils.h level.c

default: solchess

solchess: solchess.o
	gcc solchess.c utils.c level.c -lm -o solchess

clean:
	rm -f solchess
	rm -f solchess.o
