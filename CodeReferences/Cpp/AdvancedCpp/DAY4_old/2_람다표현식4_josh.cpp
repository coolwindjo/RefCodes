#include <iostream>
#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

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
	// static inline auto helper()(int a, int b)
	// {
	// 	return a + b; // error. static 멤버 함수는 멤버 데이타 접근이 안된다
	// }
	// typedef int(*F)(int, int);

	// operator F() { return &Closure::helper; } 
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	std::cout<< typeid(f1).name() <<std::endl;

	// 아래 Code들을 생각해보세요.
	decltype(f1)	f2;			// error: Compiler가 만든 Type에는 default 생성자가 "delete" 돼있음
	decltype(f1)	f3 = f1;	// OK: 복사생성자는 OK

	// C++20 부터는 Capture 하지 않은 Lambda expression은 default 생성이 가능
	// 단, Capture한 Lambda는 계속 Default 생성은 안됩니다.

	return 0;
}






