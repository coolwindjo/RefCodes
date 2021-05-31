#include <iostream>
#include <algorithm>
using namespace std;

template<typename InputIt, typename T>
InputIt efind(InputIt first, InputIt last, const T value)
{
	while (first != last) {
		if (value == *first) {
			break;
		}
		++first;
	}
	return first;
}

int main()
{
	int x[3] = { 1,2,3 };
	int* p = efind(x, x+3, 2);

	// just for checking tips by vscode
	// reverse()
	// sort()

	return 0;
}