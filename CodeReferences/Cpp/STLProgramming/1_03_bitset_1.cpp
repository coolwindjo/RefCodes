#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
using namespace std;

int main()
{
	bitset<8> b1;				// initialized with 0
	cout << b1 <<endl;
	bitset<8> b2 = 0xf0;		// 11110000
	cout << b2 <<endl;
	bitset<8> b3 = 0b11110000;
	cout << b3 <<endl;

	cout << setfill('-') << setw(32) << ""<<endl;

	b1.set();		// all set
	cout << b1 <<endl;
	b1.reset();		// all unset
	cout << b1 <<endl;
	b1.set(1);		// 0000 0010
	cout << b1 <<endl;
	b1[2] = 1;		// 0000 0110
	cout << b1 <<endl;
	b1[0].flip();	// 0000 0111
	cout << b1 <<endl;

	cout << setfill('-') << setw(32) << ""<<endl;

	if (b1.test(1) == true) {}
	if (b1[1] == true) {}
	if (b1.none() == true) {}

	const int n2 = b1.count();
	cout << n2 <<endl;	// 3

	bitset<8> b4 = 0b00001111;
	bitset<8> b5 = 0b11110000;
	bitset<8> b6 = b4 | b5;
	cout << b6 <<endl;

	cout << setfill('-') << setw(32) << ""<<endl;

	string s 		= b2.to_string();
	unsigned long n = b2.to_ulong();

	cout << s <<endl;
	cout << n <<endl;

	return 0;
}