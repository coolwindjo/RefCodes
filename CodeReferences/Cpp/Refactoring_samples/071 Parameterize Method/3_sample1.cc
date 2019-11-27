#include <limits.h>
#include <math.h>

int lastUsage()
{
	return 150;
}

int usageInRange(int start, int end)
{
	if (lastUsage() > start)
	{
		return fmin(lastUsage(), end) - start;
	}
	return 0;
}

double baseCharge()
{
	double result = usageInRange(0, 100) * 0.03;
	result += usageInRange(100, 200) * 0.05;
	result += usageInRange(200, INT_MAX) * 0.07;
	return result;
}
