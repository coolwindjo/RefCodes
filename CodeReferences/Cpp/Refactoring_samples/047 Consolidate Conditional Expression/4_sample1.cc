int onVacation(int result)
{
	return result;
}

int lengthOfService(int result)
{
	return result;
}

double getServiceLength(int vac, int los)
{
	if (onVacation(vac) && (lengthOfService(los) > 10))
	{
		return 1;
	}
	return 0.5;
}
