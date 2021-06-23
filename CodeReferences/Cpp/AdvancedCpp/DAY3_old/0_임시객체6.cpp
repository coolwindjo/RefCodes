#include <iostream>

class Test
{
public:
	//void foo() {} // error  &, && 버전과 같이 만들수 없다.

	void foo() &    // 이름 있는 객체로 호출할때..
	{
		std::cout << "foo &" << std::endl; 
	}
	void foo() && // 이름없는 객체(임시객체로) 호출할때
	{
		std::cout << "foo &&" << std::endl;
	}
};

int main()
{
	Test t;
	t.foo(); // foo() &

	Test().foo(); // foo() &&
}

