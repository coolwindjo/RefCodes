#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

/*
class ClosureType
{
public:
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
	// static 멤버 함수에는 "상수 멤버함수"라는 개념이 적용되지 않습니다.
	static inline auto helper()(int a, int b)
	{
		return a + b;
	}	
	// 객체가 함수 포인터로 변환될수 있도록 변환 연산자 함수 지원
	typedef int(*F)(int, int);

	operator F() { return &Closure::helper; } // 그런데, operator() 함수는 멤버함수이므로
												// this가 추가되는 함수..
};
*/

class ClosureType
{
	int v1, v2;
public:
	ClosureType(int v1, int v2) : v1(v1), v2(v2) {}

	inline auto operator()(int a, int b) const
	{
		return a + b + v1 + v2;
	}
	static inline auto helper()(int a, int b)
	{
		return a + b + v1 + v2; // error. static 멤버 함수는 멤버 데이타 접근이 안된다
	}
	typedef int(*F)(int, int);
	operator F() { return &Closure::helper; } 
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	// 람다표현식을 함수 포인터에 담을수 있습니다.
	//int(*f)(int, int) = [](int a, int b) { return a + b; }; 
					// ClosureType().operator 함수포인터타입() 

	int v1 = 10, v2 = 20;
	int(*f)(int, int) = [v1, v2](int a, int b) { return a + b; };

	// 결론 : 지역변수를 "캡쳐 하지 않은 람다표현식만" 함수 포인터로 변환가능 합니다.
	//			캡쳐한 람다 표현식은 함수포인터로 변환될수 없습니다.
}








