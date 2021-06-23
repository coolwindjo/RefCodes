#include <iostream>
#include <type_traits>

// 현재 C++은 "특정 타입" 에 따른 함수 오버로딩을 지원 합니다.
void foo(int)    {}
void foo(double) {}

//foo(1);
//foo(3.4);

// "타입"이 아닌 "특정 조건을 만족하는 타입들"에 따른 오버로딩은 있으면
// 좋지 않을까요 ?
//void goo(가상함수가있는클래스들) {}
//void goo(가상함수가없는클래스들) {}

// std::is_polymorphic_v<T> : 가상함수가 있으면 true, 없으면 false 

template<typename T> 
std::enable_if_t< std::is_polymorphic_v<T>, void> 
goo(T a)
{
	std::cout << "가상함수가 있는 타입에 대한 알고리즘" << std::endl;
}

template<typename T> 
std::enable_if_t< !std::is_polymorphic_v<T>, void>
goo(T a)
{
	std::cout << "가상함수가 없는 타입에 대한 알고리즘" << std::endl;
}

class Test
{
public:
//	virtual void foo() {}
};

int main()
{
	Test t;
	goo(t);
//	find(x, x + 10, 3);
//	find(x, x + 10, []() {});
}





