#include <math.h>

int lastUsage()
{
	return 150;
}

double baseCharge()
{
	double result = fmin(lastUsage(), 100) * 0.03;
	if (lastUsage() > 100)
	{
		result += (fmin(lastUsage(), 200) - 100) * 0.05;
	}
	if (lastUsage() > 200)
	{
		result += (lastUsage() - 200) * 0.07;
	}
	return result;
}
