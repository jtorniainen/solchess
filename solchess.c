#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"

#define MAX_DATA 100

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

#define EMPTY  ' '
#define PAWN   'p'
#define ROOK   'r'
#define QUEEN  'q'
#define KING   'K'
#define BISHOP 'b'
#define KNIGHT 'k'

void textcolor(int attr, int fg, int bg)
{	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int check_knight_move(int target, int dest)
{
	int diff_x = abs(get_x(target) - get_x(dest));
	int diff_y = abs(get_y(target) - get_y(dest));

	if (diff_x == 2 && diff_y == 1)
	{
		return 1;
	}
	else if (diff_x == 1 && diff_y == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_bishop_move(int target, int dest)
{
	int diff_x = abs(get_x(target) - get_x(dest));
	int diff_y = abs(get_y(target) - get_y(dest));
	if (diff_x == diff_y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_rook_move(int target, int dest)
{
	int diff_x = abs(get_x(target) - get_x(dest));
	int diff_y = abs(get_y(target) - get_y(dest));
	if (diff_x == 0 || diff_y == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_pawn_move(int target, int dest)
{
	int diff_x = abs(get_x(target) - get_x(dest));
	int diff_y = abs(get_y(target) - get_y(dest));

	if (diff_x == 1 && diff_y == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_king_move(int target, int dest)
{
	int x0 = get_x(target);
	int y0 = get_y(target);
	int x1 = get_x(dest);
	int y1 = get_y(dest);

	int manhattan = abs(x0 - x1) + abs(y0 - y1);
	int diagonal = check_pawn_move(target, dest);

	if (manhattan == 1 || diagonal == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_queen_move(int target, int dest)
{
	int rook = check_rook_move(target, dest);
	int bish = check_bishop_move(target, dest);
	printf("ROOK=%d BISHOP=%d\n", rook, bish);
	if (check_rook_move(target, dest) || 
		check_bishop_move(target, dest))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// ---------------------- //
// Check if move is valid //
// ---------------------- //
int check_move(char piece, int target, int dest)
{
	switch(piece)
	{
		case ROOK:
			printf("Moving a rook\n");
			return check_rook_move(target, dest);
		case KNIGHT:
			printf("Moving a knight\n");
			return check_knight_move(target, dest);
		case PAWN:
			printf("Moving a pawn\n");
			return check_pawn_move(target, dest);
		case BISHOP:
			printf("Moving a bishop\n");
			return check_bishop_move(target, dest);
		case QUEEN:
			printf("Moving a queen\n");
			return check_queen_move(target, dest);
		case KING:
			printf("Moving a king\n");
			return check_king_move(target, dest);
		default:
			printf("Piece not recognized!\n");
			break;
	}

	return 0;
}

void place_piece(char *board, int index, char piece)
{
	board[index] = piece;
}

void move_piece(char *board, int target, int dest)
{
	char piece = board[target];
	if (piece != EMPTY && check_move(piece, target, dest) == 1 && board[dest] != EMPTY)
	{
		board[dest] = piece;
		board[target] = EMPTY;
	}
	else
	{
		printf("Illegal move, sucker!\n");
	}
}

int check_for_victory(char *board)
{

	int count = 0;

	for (int i=0; i < strlen(board); i++)
	{
		if (board[i] != EMPTY)
		{
			count++;
		}

		if (count > 1)
		{
			return 0;
		}
	}

	return 1;

}


int randint(int range)
{
	return rand() % range;
}

void draw_board2(char *board)
{
	printf(" %sA  B  C  D%s\n", KRED, KNRM);
	for (int i=0; i<strlen(board); i++)
	{
		printf(" %c ",board[i]);
		if ((i + 1)%4 == 0)
		{
			printf("%s%d%s\n",KRED, (i + 1)/4, KNRM);
		}
	}
	printf("\n");
}

void draw_board(char *board)
{
	printf("abcd\n");
	int row=0;
	for (int i=0; i<strlen(board); i++)
	{
		if ((i + 1 + row)%2 == 0)
		{
			textcolor(BRIGHT, RED, WHITE);
		} else
		{
			textcolor(BRIGHT, RED, MAGENTA);
		}
		printf("%c",board[i]);
		textcolor(RESET, WHITE, BLACK);

		if ((i + 1)%4 == 0)
		{
			printf("%d\n",(i + 1)/4);
			row++;
		}
	}
	printf("\n");
}

int valid_pos(char *pos)
{
	printf("checking %s\n", pos);

	if (pos != NULL && 
		(int)pos[0] >= 97 && 
		(int)pos[0] <= 100 && 
		isdigit(pos[1]))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void parse_move(char *board, char *string)
{
	system("clear");
	char *part;
	int src = -1;
	int dst = -1;

	printf("victory status=%d\n", check_for_victory(board));

	part = strtok(string, " ");

	if (strcmp(part, "mov") == 0)
	{
		printf("You issued a MOV command!\n");
		part = strtok(NULL, " ");
		if (valid_pos(part))
		{
			src = get_position(part);
		}

		part = strtok(NULL, " ");
		if (valid_pos(part))
		{
			dst = get_position(part);
		}

		printf("%d -> %d\n", src, dst);
		move_piece(board, src, dst);

	}
	else
	{
		printf("Command not recognized!");
	}

	char s[10];
	fgets(s, 10, stdin);
}


int main()
{
	char input[MAX_DATA];
	/*char board[17] = "++++++++++++++++";*/
	char board[17] = "                ";
	srand(time(NULL));
	//place_piece(board, randint(16), KING);
	place_piece(board, 1, KING);
	place_piece(board, 2, PAWN);
	place_piece(board, 7, PAWN);
	while (1)
	{
		system("clear");
		draw_board(board);
		// Lets read some inputs
		printf("> ");
		char *in = NULL;
		in = fgets(input, MAX_DATA - 1, stdin);
		printf("You typed %s\n", in);
		if (in[0] == 'q')
		{
			return 0;
		}
		else if (strcmp(in, "undo") == 0)
		{
			// undo last move
		}
		else if (strcmp(in, "reset") == 0)
		{
			// reset the board
		}
		else
		{
			parse_move(board, in);
		}
	}
}
