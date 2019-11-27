#include "3_Replace_Temp_with_Query.h"

int quantity = 10;
int itemPrice = 15000;

int getBasePrice()
{
	return quantity * itemPrice;
}

double getDiscountFactor()
{
	if (getBasePrice() > 1000)
	{
		return 0.95;
	}
	return 0.98;
}

double getPrice()
{
	return getBasePrice() * getDiscountFactor();
}
