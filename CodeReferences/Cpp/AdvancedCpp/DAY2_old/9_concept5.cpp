#include <iostream>
#include <type_traits>
#include <concepts> // �̸� ���ǵ� ����.. 

template<typename T>
void foo(T a) 
{
	// T�� int�� ���ڷ� �ؼ� ȣ�Ⱑ���� Ÿ������ ����
	bool b = std::predicate<T, int>;

	std::cout << b << std::endl;
}

int main()
{
	foo( 10 );  // false 
	foo( [](int a) { return a < 0; } ); // true

	bool b1 = std::integral<int>;
	bool b2 = std::integral<double>;

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
}
