#include <iostream>

// (�Լ����ø����� T�� ��������)
// ġȯ�� ���� �Ѱ��� ������ �ƴϴ�.

// Substitution Failure Is Not An Error => "SFINAE"
// C++11 �� �ƴ� ���� ���� ���Ǵ� ���.

template<typename T>
typename T::type foo(T a)  { std::cout << "T" << std::endl; return 0; }
// int::type foo(int a) {....}

void foo(...) { std::cout << "..." << std::endl; }

int main()
{
	foo(3); 
}