double disabilityAmount(int seniority, int monthDisability, int isPartTime)
{
	if (seniority < 2)
	{
		return 0;
	}
	if (monthDisability > 12)
	{
		return 0;
	}
	if (isPartTime)
	{
		return 0;
	}
	return 10000;
}
