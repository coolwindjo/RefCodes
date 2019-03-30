#include "sample1.h"

void AccountType::SetInterestRate(double arg)
{
	interest_rate_ = arg;
}

double AccountType::GetInterestRate()
{
	return interest_rate_;
}

double Account::InterestForAmount_Days(double amount, int days)
{
	return type_.GetInterestRate() * amount * days / 365;
}
