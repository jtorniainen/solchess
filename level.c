// Testing script for level structures
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "level.h"


void read_level(char *level)
{
	// Trying to read level specifications from file
	FILE *fp;
	char *pieces = NULL;
	char *positions = NULL;
	size_t len = 0;
	ssize_t read = 0;

	// Level files contain two strings, first string contains the pieces
	// and the second one the starting locations
	// Example: 001.lvl
	//
	//		ppK
	//		c1d2b1
	//
	fp = fopen("001.lvl", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	read = getline(&pieces, &len, fp);  	// Read pieces string
	read = getline(&positions, &len, fp);  	// Read positions string
	fclose(fp);

	int num_of_pieces = strlen(pieces) - 1;

	// Convert positions to integer array
	int pos[num_of_pieces];

	for (int i = 0; i < strlen(positions) - 2; i+=2)
	{
		char loc[2];
		strncpy(loc, positions + i, 2);
		pos[(int)(i/2)] = get_position(loc);
	}

	for (int i = 0; i < strlen(level) - 1; i++)
	{
		for (int j = 0; j < strlen(pieces) - 1; j++)
		{
			if (i == pos[j])
			{
				level[i] = pieces[j];
			}
		}
	}
}

/*int main()*/
/*{*/
	/*char new_level[17] = "                ";*/
	/*read_level(new_level);*/
	/*printf("Final level: >%s<\n", new_level);*/
	/*return 0;*/
/*}*/
