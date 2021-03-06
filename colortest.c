#include <stdio.h>

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

void textcolor(int attr, int fg, int bg);

int main()
{	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if ((j + 1 + i)%2 == 0)
			{
				textcolor(BRIGHT, BLACK, WHITE);
			} else
			{
				textcolor(BRIGHT, BLACK, BLUE);
			}
			printf(" ");
			textcolor(RESET, WHITE, BLACK);
		}
		printf("\n");
	}
	return 0;
}

void textcolor(int attr, int fg, int bg)
{	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

