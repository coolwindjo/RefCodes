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
