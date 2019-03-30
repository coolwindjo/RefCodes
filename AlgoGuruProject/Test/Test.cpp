#include <iostream>

using namespace std;

int main()
{
	int	cnt = 0;
	
	for(size_t i = 0; i < 1e9; i++)
	{
		/* code */
		
		if (i % 10 == 0) {
			cout << "[LND]";
			/* code */
		}
		
		cout << cnt++ <<endl;

	}
	
	return 0;
}