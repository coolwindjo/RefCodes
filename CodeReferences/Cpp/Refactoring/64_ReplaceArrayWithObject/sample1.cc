#include <stdlib.h>
#include <string.h>

char row[3][50];

int setScore(char* name, char* wins, char* losses)
{
	strcpy(row[0], name);
	strcpy(row[1], wins);
	strcpy(row[2], losses);
	return atoi(row[1]) + atoi(row[2]);
}
