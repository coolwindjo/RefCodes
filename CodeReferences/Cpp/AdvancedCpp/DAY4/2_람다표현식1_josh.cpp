#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

// 람다 표현식의 원리
// Lambda expression을 보고 compiler가 만든 class
class ClosureType
{
private:
	
public:
	ClosureType() {}
	~ClosureType() {}
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
};

int main()
{
	// std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	// auto p = std::find_if(std::begin(v), std::end(v), [](int a) { return a % 3 == 0; });

	// auto f1 = [](int a, int b) { return a + b; };

	// Lambda expression: compiler가 생성한 Class의 임시 객체
	auto f1 = ClosureType();

	// 함수처럼 사용가능
	int n = f1(1, 2);	// f1.operator()(1, 2) 의 모양

	// 다음 중 Error를 고르세요.
	auto 		a1 = [](int a, int b) { return a + b; };	// OK
	// auto& 		a2 = [](int a, int b) { return a + b; };	// Error
	const auto&	a3 = [](int a, int b) { return a + b; };	// OK
	auto&& 		a4 = [](int a, int b) { return a + b; };	// OK
}






