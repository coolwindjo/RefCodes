#include <math.h>

double price(int quantity, double itemPrice)
{
	const double basePrice = quantity * itemPrice;
	const double quantityDiscount = fmax(0, quantity - 500) * itemPrice * 0.05;
	const double shipping = fmin(basePrice * 0.1, 100.0);
	return basePrice - quantityDiscount + shipping;
}
