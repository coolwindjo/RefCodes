#include <math.h>

double basePrice(int quantity, double itemPrice)
{
	return quantity * itemPrice;
}

double quantityDiscount(int quantity, double itemPrice)
{
	return fmax(0, quantity - 500) * itemPrice * 0.05;
}

double price(int quantity, double itemPrice)
{
	// ������(price) = �� ���ž�(base price) - �뷮 ���� ����(quantity discount)
	//               + ��ۺ�(shipping)
	return basePrice(quantity, itemPrice) - quantityDiscount(quantity, itemPrice)
			+ fmin(quantity * itemPrice * 0.1, 100.0);
}
