int quantity = 10;
int itemPrice = 15000;

double getPrice()
{
	int basePrice = quantity * itemPrice;
	double discountFactor;
	if (basePrice > 1000)
	{
		discountFactor = 0.95;
	}
	else
	{
		discountFactor = 0.98;
	}
	return basePrice * discountFactor;
}
