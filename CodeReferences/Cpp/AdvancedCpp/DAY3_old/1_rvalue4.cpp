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

	// 10, 3.4 등의 literal은 rvalue 지만..
	// 문자열 literal 은 lvalue 입니다.
}



/*
int main()
{
	int n = 0;

	++n; // lvalue

	if (std::is_lvalue_reference_v< decltype(( 표현식 )) >)
		std::cout << "lvalue" << std::endl;
	else
		std::cout << "rvalue" << std::endl;
}

*/
