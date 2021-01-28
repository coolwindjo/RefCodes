// 6_reference_wrapper1 - 꼭 알아 두세요.. C++11에 나왔는데..
//								C++20에서 비슷한 개념이 여러개 등장
#include <iostream>
#include <functional>

template<typename T> class reference_wrapper
{
	T* obj;
public:
	reference_wrapper(T& arg) : obj(&arg) {}

	// 진짜 참조로 변환되게
	operator T&() { return *obj; }
};

int main()
{
	int n1 = 10;
	int n2 = 20;

	reference_wrapper<int> r1 = n1;
	reference_wrapper<int> r2 = n2;

	r1 = r2; // 대입연산자..

	// r1이 진짜 참조와 호환되게 하자.
	int& r3 = r1;  // r3.operator int&() 

	std::cout << n1 << std::endl;	
	std::cout << n2 << std::endl;	
	std::cout << r1 << std::endl;	
	std::cout << r2 << std::endl;	
}