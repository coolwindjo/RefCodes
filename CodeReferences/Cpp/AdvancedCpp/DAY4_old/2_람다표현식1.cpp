#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;



// 람다 표현식의 원리
// 람다 표현식을 보고 컴파일러가 만든 클래스
class ClosureType
{
public:
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
};
int main()
{
//	auto f1 = [](int a, int b) { return a + b; };
	// 람다표현식 : 컴파일러가 생성한 클래스의 임시객체
	auto f1 = ClosureType();

	// 함수 처럼 사용가능
	int n = f1(1, 2); // f1.operator()(1,2) 의 모양

	// 다음중 에러를 고르세요.
	auto        a1 = [](int a, int b) { return a + b; }; // ok
	auto&       a2 = [](int a, int b) { return a + b; }; // error
	const auto& a3 = [](int a, int b) { return a + b; }; // ok
	auto&&      a4 = [](int a, int b) { return a + b; }; // ok













	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	auto p = std::find_if(std::begin(v), std::end(v), [](int a) { return a % 3 == 0; });
}






