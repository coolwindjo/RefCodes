#include <math.h>

double basePrice(int quantity, double itemPrice)
{
	return quantity * itemPrice;
}

double quantityDiscount(int quantity, double itemPrice)
{
	return fmax(0, quantity - 500) * itemPrice * 0.05;
}

double shipping(int quantity, double itemPrice)
{
	return fmin(basePrice(quantity, itemPrice) * 0.1, 100.0);
}

double price(int quantity, double itemPrice)
{
	return basePrice(quantity, itemPrice) - quantityDiscount(quantity, itemPrice)
			+ shipping(quantity, itemPrice);
}
