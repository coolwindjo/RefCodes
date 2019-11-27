#include <stdio.h>
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
			for (int j = 0; j < 2; ++j)
			{
				if (!found)
				{
					printf("%d, %d\n", i, j);
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
		}
	}
	return found;
}
