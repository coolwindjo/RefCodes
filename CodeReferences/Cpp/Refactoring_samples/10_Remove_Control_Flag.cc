#include "10_Remove_Control_Flag.h"
#include <string.h>

void sendAlert()
{
}

int checkSecurity(char** people, int peopleLength)
{
	int found = 0;
	for (int i = 0; i < peopleLength; ++i)
	{
		if (!found)
		{
			if (strcmp(people[i], "Don") == 0)
			{
				sendAlert();
				found = 1;
			}
			if (strcmp(people[i], "John") == 0)
			{
				sendAlert();
				found = 1;
			}
		}
	}
	return found;
}
