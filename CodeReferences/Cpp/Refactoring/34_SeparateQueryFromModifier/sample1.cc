#include <string.h>

void sendAlert()
{
}

char* foundMiscreant(char* people[], int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (!strcmp(people[i], "Don"))
		{
			sendAlert();
			return "Don";
		}
		if (!strcmp(people[i], "John"))
		{
			sendAlert();
			return "John";
		}
	}
	return "";
}

int checkSecurity(char* people[], int length)
{
	char* found = foundMiscreant(people, length);
	return strlen(found);
}
