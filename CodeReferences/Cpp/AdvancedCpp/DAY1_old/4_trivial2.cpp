#include <iostream>
#include <type_traits> // C++11 의 type traits 라이브러리.
						// 타입에 대한 다양한 정보 조사.

// 핵심 : trivial 여부를 조사하는 방법.

class Test
{
	int data = 10; // 이 코드 때문에 컴파일러가 만든 디폴트 생성자는
					// trivial 하지 않습니다.
public:
	void goo() {}
//	virtual void foo() {}

//	Test(){} // 구현에 아무 코드도 없지만, 컴파일러는 생성자가 하는일이 있다고
				// 생각해게 됩니다. trivial 하지 않습니다.

	Test() = default; // C++11 의 새로운 문법
					// 인자없는(디폴트) 생성자를 만들어 달라는 의미.
			// : data(10) {}

	Test(int a, int b) {}
};

int main()
{
	Test t;
	bool b = std::is_trivially_default_constructible_v<Test>;

	

	std::cout << b << std::endl;
}