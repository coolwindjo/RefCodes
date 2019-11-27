#include <iostream>

using namespace std;

/// Primary template
template<bool, typename T, typename U> 
struct IfThenElse { typedef T type; };

/// Partial specialization
template<typename T, typename U> 
struct IfThenElse<false, T, U> { typedef U type; };


template<int N>
struct Bit
{
	//using data_type = unsigned int;

	using data_type = 
		typename IfThenElse< N <= 8, 
			char, 
			typename IfThenElse< N <= 16, unsigned short, unsigned int>::type
			>::type;

	data_type data;
};

int main()
{
	IfThenElse<true, int, double>::type n1; // int
	IfThenElse<false, int, double>::type n2; // double

	Bit<8> b1;	/// 8 bit 를 관리하기 위한 Object
	Bit<16> b2;	/// 16 bit 를 관리하기 위한 Object
	Bit<32> b3;	/// 32 bit 를 관리하기 위한 Object

	cout << sizeof(b1) << endl;
	cout << sizeof(b2) << endl;
	cout << sizeof(b3) << endl;

	system("pause");
	return 0;
}