#include <string.h>
#include <iostream>

using namespace std;

int alert_on = 0;

int checkAlert() {return alert_on;}

void sendAlert()
{
	alert_on = 1;
}

char* foundPerson(char* people[], int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (!strcmp(people[i], "Don"))
		{
			return "Don";
		}
		if (!strcmp(people[i], "John"))
		{
			return "John";
		}
	}
	return "";
}

//char* foundMiscreant(char* people[], int length)
char* foundPersoneAndSendAlert(char* people[], int length)
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
//	return strlen(foundPersoneAndSendAlert(people, length));
	char* found = foundPerson(people, length);

	if (strcmp(found, ""))
	{
		sendAlert();
	}
	cout << "found: "<< found <<endl;
	return strlen(found);
}
