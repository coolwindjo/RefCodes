#include <math.h>

double price(int quantity, double itemPrice)
{
	// 결제액(price) = 총 구매액(base price) - 대량 구매 할인(quantity discount)
	//               + 배송비(shipping)
	const double basePrice = quantity * itemPrice;
	return basePrice - fmax(0, quantity - 500) * itemPrice * 0.05
			+ fmin(basePrice * 0.1, 100.0);
}
