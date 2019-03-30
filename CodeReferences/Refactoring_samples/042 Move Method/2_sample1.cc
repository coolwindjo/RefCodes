#include "sample1.h"

bool AccountType::IsPremium()
{
	return true;
}

double AccountType::OverdraftCharge(int days_overdrawn)
{
	if (IsPremium())
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
		result += type.OverdraftCharge(days_overdrawn);
	}
	return result;
}
