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
	double result;
	if (isDead)
	{
		result = deadAmount();
	}
	else
	{
		if (isSeparated)
		{
			result = separatedAmount();
		}
		else
		{
			if (isRetired)
			{
				result = retiredAmount();
			}
			else
			{
				result = normalPayAmount();
			}
		}
	}
	return result;
}
