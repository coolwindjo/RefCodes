#include <iostream>
#include <algorithm>
#include <functional>  
#include <vector>

class ClosureType
{
private:
	// Member variables
	int v1;
	int v2;
	
public:
	ClosureType(int v1, int v2) : v1(v1), v2(v2) {}
	~ClosureType() {}
	inline auto operator()(int a, int b) const
	{
		return a + b + v1 + v2;
	}
};

int main()
{
	// Local variables
	int v1 = 10;
	int v2 = 20;

	auto f1 = [v1, v2](int a, int b) { return a + b + v1 + v2; };
			// ClosureType(v1, v2) 로 변경
	std::cout<< sizeof(f1) <<std::endl;	// 8

	// mutable lambda expression: () 연산자를 비 상수 Member 함수로 해달라!
	// auto f1 = [v1, v2](int a, int b) { v1 = 10; return a + b + v1 + v2; };
	auto f2 = [v1, v2](int a, int b) mutable { v1 = 10000; return a + b + v1 + v2; };
	auto f3 = [&v1, &v2](int a, int b) mutable { v1 = 1000; return a + b + v1 + v2; };

	return 0;
}