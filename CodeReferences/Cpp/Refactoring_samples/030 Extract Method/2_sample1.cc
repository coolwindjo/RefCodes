#include <iostream>
#include <vector>

using namespace std;

string name("Kim");
vector<double> orders;

void InitOrders()
{
	for (int i = 0; i < 5; ++i)
	{
		orders.push_back(i);
	}
}

void PrintBanner()
{
	cout << "**************************" << endl;
	cout << "***** Customer Owes ******" << endl;
	cout << "**************************" << endl;
}

void PrintOwing()
{
	double outstanding(0.0);

	InitOrders();
	PrintBanner();

	// calculate outstanding
	vector<double>::const_iterator orders_it = orders.begin();
	while (orders_it++ != orders.end())
	{
		outstanding += *orders_it;
	}

	// print details
	cout << "name:" + name << endl;
	cout << "amount:" << outstanding << endl;
}

int main()
{
	PrintOwing();
}
