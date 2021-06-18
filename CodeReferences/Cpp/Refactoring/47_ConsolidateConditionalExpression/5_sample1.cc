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
	return onVacation(vac) && (lengthOfService(los) > 10) ? 1 : 0.5;
}
