#include <stdlib.h>
#include <string.h>

struct Score {
	char name[50];
	int wins;
	int losses;
} row;

int setScore(char* name, char* wins, char* losses)
{
	strcpy(row.name, name);
	row.wins = atoi(wins);
	row.losses = atoi(losses);
	return row.wins + row.losses;
}
