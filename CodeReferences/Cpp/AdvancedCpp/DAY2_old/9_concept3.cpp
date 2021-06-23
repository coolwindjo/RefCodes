#include <iostream>
#include <type_traits>

// Ÿ���� �������ϴ� ������ ����ϴ� "Concept ������ ����"
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
	a + b;   // ������ �����ؾ� �Ѵٴ� ����
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
	//	foo(3.3); // double - 1��
	foo(3);   // abiguous error.  1���� 2���� ��� ����.
}