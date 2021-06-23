#include <iostream>
#include <type_traits>

#define CHECK_VALUE_CATEGORY( ... )								\
	if (std::is_lvalue_reference_v< decltype(( __VA_ARGS__ )) >)\
		std::cout << "lvalue" << std::endl;						\
	else                                                        \
		std::cout << "rvalue" << std::endl;

int main()
{
	int n = 10;

	CHECK_VALUE_CATEGORY(n);
	CHECK_VALUE_CATEGORY(10);
	CHECK_VALUE_CATEGORY(++n);
	CHECK_VALUE_CATEGORY(n++);

	CHECK_VALUE_CATEGORY("Hello"); // lvalue..

	// 10, 3.4 ���� literal�� rvalue ����..
	// ���ڿ� literal �� lvalue �Դϴ�.
}



/*
int main()
{
	int n = 0;

	++n; // lvalue

	if (std::is_lvalue_reference_v< decltype(( ǥ���� )) >)
		std::cout << "lvalue" << std::endl;
	else
		std::cout << "rvalue" << std::endl;
}

*/
