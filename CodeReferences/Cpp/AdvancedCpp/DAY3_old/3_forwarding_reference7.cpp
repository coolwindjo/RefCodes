#include <vector>
#include <iostream>
// Effective Modern C++
// Effective C++ 3/e,  More Effective C++
int main()
{
	std::vector<int>  v1 = { 1,1,1 };
	std::vector<bool> v2 = { 1,1,1 };

	// a1과 a2의 타입을 예측해 보세요
	auto a1 = v1[0]; // int a1 = v1[0]
	auto a2 = v2[0]; // BitProxy 같은 클래스 a2 = v2[0]

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;

	// 아래 코드 생각해 보세요
	auto& r1 = v1[0]; //  ok.. operator[] 연산자가 참조 반환
	//auto& r2 = v2[0]; //  error. operator[] 가 임시객체(rvalue)반환.
	auto&& r3 = v2[0]; // ok

	//for (auto& n : v2) {}// error
}
