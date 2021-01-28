#include <iostream>
#include <functional>
using namespace std::placeholders;

void foo(int& a, int n) { a = 300; }

int main()
{	
	std::function<void(int)> f; // C++11 function
								// 함수포인터 역활..

	// bind는 인자를 "참조가 아닌 값"으로 고정하게 됩니다. 이유는 아래 {}이 있다고 생각해보세요
//	{
		int n = 0;

//		f = std::bind(&foo, n, _1); // 1번째 인자를 "n"으로 고정했을까요 ?
									//	"n의 값(0)"으로 고정했을까요 ?  =====> 정답...
		f = std::bind(&foo, std::ref(n), _1); // ok.. 참조로 고정..
//	}

	f(10); // foo(n, 10) 이 아니고
		   // foo(0, 10) 이 표현..

	std::cout << n << std::endl; // 
}