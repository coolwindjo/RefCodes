#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

// 출제 의도 SFINAE 의 개념을 이해하고.. 특정 멤버가 있는지를 조사하는 방법에 대한 아이디어..

// 핵심 : 특정 멤버 함수가 존재하면 에러가 나오지 않고, 존재하지 않으면 에러가 나오게 하는 코드를 찾아야 한다.

// 방법 1. resize() 함수의 리턴 타입에 포인터를 더한 타입을 사용해서 인자를 받는 기술


// 아래 Test에서 resize를 주석 처리하고 실행해 보세요
class Test
{
public:
//	Test(int n) {}
	void resize(int n) {}
};

template<typename T> void foo(typename  add_pointer<decltype( T().resize(0))>::type    p)	// 이코드의 문제점은 T에 디폴트 생성자가 없을 경우 입니다. Test(int) 생성자의 주석을 제거해 보세요..
{															// 해결책은 main 함수 아래에 주석으로 되어있는 코드입니다.
	cout << "resize 가 있습니다." << endl;
}

template<typename T> void foo(...)
{
	cout << "resize가 없습니다." << endl;
}

int main()
{
	foo<Test>(0);
}

/*
template<typename T> void foo(typename  add_pointer<decltype(declval<T>().resize(0))>::type p)	// 이 코드는 T에 디폴트 생성자가 없어도 됩니다.
{															
	cout << "resize 가 있습니다." << endl;
}
*/