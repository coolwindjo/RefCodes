#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char szLine[128] = { 0, };
	char* cB;
	for (size_t i = 0; i < 100; i++)
	{
		int a = 0;
		int b = 0;
		char* pch = fgets(szLine, 128, stdin);
		if (pch != nullptr)
		{
			a = atoi(strtok(szLine, " "));
			cB = strtok(NULL, " ");
			if (cB != nullptr)
			{
				b = atoi(cB);
			}
		}

		cout << a+b << endl;
	}

	return 0;
}
