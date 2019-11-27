#include <iostream>
#include "5_Introduce_Parameter_Object.h"

using namespace std;

Entry::Entry(double value, time_t charge_date)
		: value_(value), charge_date_(charge_date)
{
}

time_t Entry::GetDate()
{
	return charge_date_;
}

double Entry::GetValue()
{
	return value_;
}

void Account::Init()
{
	for (int i = 0; i < 5; ++i)
	{
		entries_.push_back(Entry(100, time(0) - i * OneDay()));
	}
}

void Account::PrintDate()
{
	for (vector<Entry>::iterator it = entries_.begin(); it != entries_.end(); it++)
	{
		time_t rawtime = it->GetDate();
		cout << ctime(&rawtime) << endl;
	}
}

double Account::GetFlowBetween(time_t start, time_t end)
{
	double result;
	for (vector<Entry>::iterator it = entries_.begin(); it != entries_.end(); it++)
	{
		if (it->GetDate() >= start && it->GetDate() <= end)
		{
			result += it->GetValue();
		}
	}
	return result;
}

int Account::OneDay()
{
	return 24 * 60 * 60;
}
