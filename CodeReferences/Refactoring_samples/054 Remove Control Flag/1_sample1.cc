#include <string.h>

void sendAlert()
{
}

int checkSecurity(char** people, int peopleLength)
{
	for (int i = 0; i < peopleLength; ++i)
	{
		if (strcmp(people[i], "Don") == 0)
		{
			sendAlert();
			break;
		}
		if (strcmp(people[i], "John") == 0)
		{
			sendAlert();
			break;
		}
	}
	return 0;
}
