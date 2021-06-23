#include <iostream>

// 2번에서 만든 Mul을 람다표현식으로 만들어 봅시다.
//auto f1 = [](int a, int b) { return a * b; }; // C++11

//auto f1 = [](auto a, auto b)  { return a * b; }; // C++14
//  template<typename T1, typename T2> auto operator()(T1 a, T2 b) {return a * b;}

auto f1 = [](auto a, decltype(a) b) { return a * b; }; 

// 그래서 C++20 에서는 람다표현식에서 템플릿 사용이 가능해집니다.
auto f1 = []<typename T> (T a, T b) { return a * b; }; // C++20 표기법


int main()
{
	std::cout << f1(1, 2)     << std::endl;
	std::cout << f1(1.2, 2.2) << std::endl;

	std::cout << f1(1,   2.2) << std::endl;

	// 그런데... 1, 2번째 인자가 같도록 제한 할수 없을까 ?
	// swap(a, b) 등을 만들때는 a,b 가 같을 때만 동작해야 한다.
}

