#include <iostream>

class Test
{
public:
	// void foo() {}	// Error. &, && Version과 같이 만들 수 없다.

	void foo() &	// 이름 있는 객체로 호출할 때..
	{
		std::cout << "foo &" << std::endl;
	}
	void foo() &&	// 이름 없는 객체(임시 객체)로 호출할 때..
	{
		std::cout << "foo &&" << std::endl;
	}
};

int main()
{
	Test t;
	t.foo();

	Test().foo();
}