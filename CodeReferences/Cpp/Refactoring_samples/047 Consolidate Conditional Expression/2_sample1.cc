int isNotEligibleForDisability(int seniority, int monthDisability, int isPartTime)
{
	return (seniority < 2) || (monthDisability > 12) || (isPartTime);
}

double disabilityAmount(int seniority, int monthDisability, int isPartTime)
{
	if (isNotEligibleForDisability(seniority, monthDisability, isPartTime))
	{
		return 0;
	}
	return 10000;
}
