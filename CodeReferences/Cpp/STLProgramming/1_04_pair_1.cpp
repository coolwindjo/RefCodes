#include <iostream>
// #include <utility>	// for pair, but optional (iostream has it, too.)
using namespace std;

#if 0
template<typename T1, typename T2> struct pair
{
	T1 first;
	T2 second;
	// ....
};
#endif

// return two values
pair<int, double> foo() 
{
	return pair<int, double>(1, 3.4);
}

int main() 
{
	pair<int, double> p1(1, 3.4);

	cout << p1.first <<endl;
	cout << p1.second <<endl;
	return 0;
}