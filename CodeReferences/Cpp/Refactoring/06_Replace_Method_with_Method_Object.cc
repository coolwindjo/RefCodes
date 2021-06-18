#include "6_Replace_Method_with_Method_Object.h"
#include <iostream>

using namespace std;

double Account::delta()
{
	return 0.1;
}
int Account::gamma(int inputVal, int quantity, int yearToDate)
{
	int importantValue1 = (inputVal * quantity) + delta();
	int importantValue2 = (inputVal * yearToDate) + 100;
	if ((yearToDate - importantValue1) > 100) {
		importantValue2 -= 20;
	}
	int importantValue3 = importantValue2 * 7;
//	cout << "Test Print: " << importantValue3 - 2 * importantValue1 <<endl;
	return importantValue3 - 2 * importantValue1;
}
