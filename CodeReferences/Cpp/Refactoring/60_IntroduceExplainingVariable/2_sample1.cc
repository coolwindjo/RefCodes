#include <math.h>

double price(int quantity, double itemPrice)
{
	// ������(price) = �� ���ž�(base price) - �뷮 ���� ����(quantity discount)
	//               + ��ۺ�(shipping)
	const double basePrice = quantity * itemPrice;
	const double quantityDiscount = fmax(0, quantity - 500) * itemPrice * 0.05;
	return basePrice - quantityDiscount + fmin(basePrice * 0.1, 100.0);
}
