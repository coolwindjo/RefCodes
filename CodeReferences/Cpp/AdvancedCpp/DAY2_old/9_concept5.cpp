#include <iostream>
#include <type_traits>
#include <concepts> // 미리 정의된 컨셉.. 

template<typename T>
void foo(T a) 
{
	// T가 int를 인자로 해서 호출가능한 타입인지 조사
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
