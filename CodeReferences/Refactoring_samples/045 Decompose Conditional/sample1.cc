const int SUMMER_START = 6;
const int SUMMER_END = 10;

double summerRate = 1.0;
double winterRate = 1.5;
double winterServiceCharge = 10000;

double heatingCharge(int date, int quantity)
{
	double charge = 0.0;
	if (date < SUMMER_START || date > SUMMER_END)
	{
		charge = quantity * winterRate + winterServiceCharge;
	} else {
		charge = quantity * summerRate;
	}
	return charge;
}
