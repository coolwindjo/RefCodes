#include "7_Replace_Nested_Conditional_with_Guard_Clauses.h"
#include <iostream>

using namespace std;

double deadAmount()
{
	return 200;
}

double separatedAmount()
{
	return 50;
}

double retiredAmount()
{
	return 1000;
}

double normalPayAmount()
{
	return 100;
}

double getPayAmount(int isDead, int isSeparated, int isRetired)
{
	if (isDead)
	{
		return deadAmount();
	}

	if (isSeparated)
	{
		return separatedAmount();
	}

	if (isRetired)
	{
		return retiredAmount();
	}

	return normalPayAmount();
}

double income = 500.0;
const double ADJ_FACTOR = 5;

double getAdjustedCapital(double capital, double intRate, double duration)
{
	if (capital <= 0.0)
	{
		return 0.0;
	}

	if (intRate > 0.0 && duration > 0.0)
	{
		return (income / duration) * ADJ_FACTOR;
	}
}

