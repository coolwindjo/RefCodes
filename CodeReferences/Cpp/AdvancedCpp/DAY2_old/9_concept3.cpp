#include <iostream>
#include <type_traits>

// 타입이 가져야하는 조건을 명시하는 "Concept 문법의 도입"
template<typename T>
concept MoreThan1 = sizeof(T) > 1;

template<typename T>
concept LessThan8 = sizeof(T) < 8;

template<typename T>
concept LessThan8AndMoreThan1 = MoreThan1<T> && LessThan8<T>;


template<typename T> 
concept Addable = requires(T a, T b)
{
//	typename T::value_type;
//	T();
	a + b;   // 덧셈이 가능해야 한다는 조건
};

template<typename T> requires MoreThan1<T>
void foo(T a)
{
	std::cout << "1" << std::endl;
}

//template<typename T> requires MoreThan1<T> && LessThan8<T>// && Addable<T>
template<typename T> requires LessThan8AndMoreThan1<T>
void foo(T a)
{
	std::cout << "2" << std::endl;
}

int main()
{
	//	foo(3.3); // double - 1번
	foo(3);   // abiguous error.  1번과 2번을 모두 만족.
}