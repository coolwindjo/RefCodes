double income = 500.0;
const double ADJ_FACTOR = 5;

double getAdjustedCapital(double capital, double intRate, double duration)
{
	double result = 0.0;
	if (capital > 0.0)
	{
		if (intRate > 0.0 && duration > 0.0)
		{
			result = (income / duration) * ADJ_FACTOR;
		}
	}
	return result;
}
