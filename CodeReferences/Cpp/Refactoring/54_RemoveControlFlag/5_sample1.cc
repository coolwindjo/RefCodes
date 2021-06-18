#include <stdio.h>
#include <string.h>

void sendAlert()
{
}

int checkSecurity(char** people, int peopleLength)
{
	for (int i = 0; i < peopleLength; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			printf("%d, %d\n", i, j);
			if (strcmp(people[i], "Don") == 0)
			{
				sendAlert();
				return 1;
			}
			if (strcmp(people[i], "John") == 0)
			{
				sendAlert();
				return 1;
			}
		}
	}
	return 0;
}
