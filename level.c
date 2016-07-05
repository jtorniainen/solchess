// Testing script for level structures
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


int main()
{
	// Trying to read level specifications from file
	FILE *fp;
	char *line = NULL;
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

	printf("PIECES=%sPOSITIONS=%s", pieces, positions);

	for (int i = 0; i < strlen(pieces) - 1; i++)
	{
		printf("%c\n", pieces[i]);
	}
	printf("done (len=%d)\n", strlen(pieces));


	printf("STARTING POSITIONS:\n");
	for (int i = 0; i < strlen(positions) - 2; i+=2)
	{
		char loc[2];
		strncpy(loc, positions + i, 2);
		/*int pos_int = get_position(loc);*/
		pos[(int)(i/2)] = get_position(loc);

		/*printf("%c%c -> %d\n", loc[0], loc[1], pos_int);*/
	}
	printf("done (len=%d)\n", strlen(positions));

	return 0;
}

