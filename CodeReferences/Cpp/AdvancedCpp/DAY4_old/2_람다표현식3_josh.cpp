#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

// class ClosureType
// {
// public:
// 	inline auto operator()(int a, int b) const
// 	{
// 		return a + b;
// 	}

// 	// static Member 함수에는 "상수 Member함수" 라는 개념이 적용되지 않습니다.
// 	static inline auto helper()(int a, int b)
// 	{
// 		return a + b;
// 	}

// 	// 객체가 함수 Pointer로 변환 될 수 있도록 변환 연산자 함수 지원
// 	typedef int(*f)(int, int);
// 	operator F() { return &Closure::operator(); }	// 그런데, operator() 함수는 Member함수 Pointer는 일반 함수 Pointer와 호환되지 않는다.
// 														// this 가 추가되는 함수이므로...
// };

class ClosureType
{
public:
	inline auto operator()(int a, int b) const
	{
		return a + b + v1 + v2;
	}

	// static Member 함수에는 "상수 Member함수" 라는 개념이 적용되지 않습니다.
	static inline auto helper()(int a, int b)
	{
		return a + b + v1 + v2;
	}

	// 객체가 함수 Pointer로 변환 될 수 있도록 변환 연산자 함수 지원
	typedef int(*f)(int, int);
	operator F() { return &Closure::operator(); }	// 그런데, operator() 함수는 Member함수 Pointer는 일반 함수 Pointer와 호환되지 않는다.
														// this 가 추가되는 함수이므로...
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	// Lambda expression을 함수 Pointer에 담을 수 있습니다.
	// int(*f)(int, int) = [](int a, int b) { return a + b; };
						// ClosureType().operator 함수PointerType():	객체가 함수 Pointer로 들어간다??

	// int v1 = 10;
	// int v2 = 20;
	// int(*f)(int, int) = [v1, v2](int a, int b) { return a + b; };

	// 결론: 지역 변수를 "Capture하지 않은 Lambda expression만" 함수 Pointer로 변환가능 합니다.
				// Capture한 Lambda expression은 함수 Pointer로 변환될 수 없습니다.
	return 0;
}
