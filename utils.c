#include <math.h>
#include <stdio.h>
#include "utils.h"

#define RESET		0
#define BRIGHT 		1
#define DIM			2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED			1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

// Helper function to convert coordinates
int sub2ind(int x, int y)
{
	return (int)(y * 4 + x);
}

int get_position(char *pos)
{
	int a = (int)pos[0];
	int b = (int)pos[1];

	a = a - 97;
	b = b - 49;

	float coordinate = b * 4 + a;
	int ret = sub2ind(a, b);

	return ret;
}

int get_y(int index)
{
	return (int)(floor(index / 4));
}

int get_x(int index)
{
	int y = get_y(index);
	return (int)(index - y * 4);
}
