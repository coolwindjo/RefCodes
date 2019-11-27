const int SUMMER_START = 6;
const int SUMMER_END = 10;

double summerRate = 1.0;
double winterRate = 1.5;
double winterServiceCharge = 10000;

int notSummer(int date)
{
	return date < SUMMER_START || date > SUMMER_END;
}

double summerCharge(int quantity)
{
	return quantity * summerRate;
}

double winterCharge(int quantity)
{
	return quantity * winterRate + winterServiceCharge;
}

double heatingCharge(int date, int quantity)
{
	double charge = 0.0;
	if (notSummer(date))
	{
		charge = winterCharge(quantity);
	}
	else
	{
		charge = summerCharge(quantity);
	}
	return charge;
}
