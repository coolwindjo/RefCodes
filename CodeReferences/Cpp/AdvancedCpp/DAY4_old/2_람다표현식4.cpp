#include <algorithm>
#include <functional>  
#include <vector>
#include <iostream>
using namespace std;

class ClosureType
{
//	int v1, v2;
public:
	ClosureType() = delete;
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
};
int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	std::cout << typeid(f1).name() << std::endl;

	// 아래 코드들을 생각해 보세요
	decltype(f1) f2;		// error. 컴파일러가 만든 타입에는 디폴트 생성자가 "delete" 
							// 되어 있습니다.
	decltype(f1) f3 = f1;  // ok.. 복사 생성자는 ok..

		// C++20 부터는 캡쳐하지 람다 표현식은 디폴트 생성이 가능.
		// 단, 캡쳐한 람다는 계속 디폴트 생성은 안됩니다.
}






