// 6_reference_wrapper1 - 꼭 알아 두세요.. C++11에 나왔는데..
//								C++20에서 비슷한 개념이 여러개 등장
#include <iostream>
#include <functional>

// C++ 참조 : 이동 불가능한 참조.. 대입연산시 "값의 이동"
// reference_wrapper : 이동 가능한 참조.. 대입연산시 "참조가 이동"
int main()
{
	int n1 = 10;
	int n2 = 20;

//	int& r1 = n1;
//	int& r2 = n2;
	std::reference_wrapper<int> r1 = n1;
	std::reference_wrapper<int> r2 = n2;

	r1 = r2; // 이 한줄의 의미는 ??

	// 아래 코드 결과 예측해 보세요
	//							   C++참조  reference_wrapper
	std::cout << n1 << std::endl;	// 20   10
	std::cout << n2 << std::endl;	// 20   20
	std::cout << r1 << std::endl;	// 20   20
	std::cout << r2 << std::endl;	// 20   20
}