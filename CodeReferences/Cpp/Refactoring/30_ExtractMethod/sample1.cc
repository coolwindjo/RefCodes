#include <iostream>
#include <vector>

using namespace std;

string name("Kim");
vector<double> orders;

void PrintOwing()
{
	double outstanding(0.0);

	// init orders
	for (int i = 0; i < 5; ++i)
	{
		orders.push_back(i);
	}

	// print banner
	cout << "**************************" << endl;
	cout << "***** Customer Owes ******" << endl;
	cout << "**************************" << endl;

	// calculate outstanding
	vector<double>::const_iterator orders_it = orders.begin();
	while (++orders_it != orders.end())
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
