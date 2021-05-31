#include <iostream>
#include <string>
#include <complex>

// using namespace std;
using std::cout;
using std::endl;
using std::string;

using namespace std::string_literals;	// "hello"s
using namespace std::literals;	// 3i

void foo(string s) { cout << "string" <<endl; }
void foo(const char* s) { cout << "char*" <<endl; }

int main()
{
	foo("hello");	// char*
	foo("hello"s);	// string
	// 3s	: seconds
	// 2i	: complex<double>

	std::complex<double> c = 3i;

	return 0;
}