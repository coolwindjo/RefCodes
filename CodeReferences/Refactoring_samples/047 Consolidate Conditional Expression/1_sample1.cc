double disabilityAmount(int seniority, int monthDisability, int isPartTime)
{
	if ((seniority < 2) || (monthDisability > 12) || (isPartTime))
	{
		return 0;
	}
	return 10000;
}
