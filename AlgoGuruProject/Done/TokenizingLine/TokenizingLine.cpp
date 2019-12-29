#include "../../ProbSolvStart.h"

int main()
{
	for (size_t i = 0; i < 100; i++)
	{
		int a = 0;
		int b = -1;
#if 0
		char szLine[128] = { 0, };
		char* cB;
		char* pch = fgets(szLine, 128, stdin);
		if (pch != nullptr)
		{
			a = atoi(strtok(szLine, " "));
			cB = strtok(NULL, " ");
			if (cB != nullptr)
			{
				b = atoi(cB);
			}
			else continue;
		}
		else continue;
#else
		string line;
		getline(cin, line);
		stringstream(line) >> a >> b;
		if (b == -1){
			cout <<endl;
			continue;
		}

#endif

		cout << a+b << endl;
	}

	return 0;
}
