#include "sample1.h"

bool AccountType::IsPremium()
{
	return true;
}

double Account::OverdraftCharge()
{
	if (type.IsPremium())
	{
		double result = 10;
		if (days_overdrawn > 7)
		{
			result += (days_overdrawn - 7) * 0.85;
		}
		return result;
	}
	return days_overdrawn * 1.75;
}

double Account::BankCharge()
{
	double result = 4.5;
	if (days_overdrawn > 0)
	{
		result += OverdraftCharge();
	}
	return result;
}
