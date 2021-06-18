#include "sample1.h"

double Account::InterestForAmount_Days(double amount, int days)
{
	return interest_rate_ * amount * days / 365;
}
