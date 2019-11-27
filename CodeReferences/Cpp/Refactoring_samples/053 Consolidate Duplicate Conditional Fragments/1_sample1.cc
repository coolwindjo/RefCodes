int isSpecialDeal(int result)
{
	return result;
}

void send()
{
}

double getTotal(int specialDeal)
{
	double total = 0;
	double price = 10000;

	if (isSpecialDeal(specialDeal))
	{
		total = price * 0.95;
	}
	else
	{
		total = price * 0.98;
	}
	send();

	return total;
}
