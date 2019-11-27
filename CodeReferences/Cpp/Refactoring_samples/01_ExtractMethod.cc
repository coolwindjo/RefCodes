#include "1_ExtractMethod.h"
#include <iostream>
#include <vector>

using namespace std;

string name("Kim");
vector<double> orders;

void InitOrders()
{
	// init orders
	for (int i = 0; i < 5; ++i)
	{
		orders.push_back(i);
	}
}

void PrintBanner()
{
	// print banner
	cout << "**************************" << endl;
	cout << "***** Customer Owes ******" << endl;
	cout << "**************************" << endl;
}

double CalculateOutstanding(double dOutStanding)
{
	// calculate outstanding
	vector<double>::const_iterator orders_it = orders.begin();
	while (++orders_it != orders.end())
	{
		dOutStanding += *orders_it;
	}
	return dOutStanding;
}

void PrintDetails(double dOutStanding)
{
	// print details
	cout << "name:" + name << endl;
	cout << "amount:" << dOutStanding << endl;
}

void PrintOwing()
{
	double outstanding(0.0);

	InitOrders();

	PrintBanner();

	outstanding = CalculateOutstanding(outstanding);

	PrintDetails(outstanding);
}

//int main()
//{
//	PrintOwing();
//}
