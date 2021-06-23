#include <iostream>

// (�Լ����ø����� T�� ��������)
// ġȯ�� ���� �Ѱ��� ������ �ƴϴ�.

// Substitution Failure Is Not An Error => "SFINAE"

// C++11 �� �ƴ� ���� ���� ���Ǵ� ���.

template<typename T>
typename T::type  foo(T a)  { std::cout << "T" << std::endl; return 0; }

// typename int::type foo(int a) { .... } �� �Լ��� �����Ϸ��� �Ѵ�.

void foo(...) { std::cout << "..." << std::endl; }

int main()
{
	// ��� �Լ��� ��������� "�Լ�����"�� ���� ����
	foo(3);  // 1. foo ���ø��� ����ϱ�� ����
			 //    => �׷���.. �Լ��� ����� ��.. ����.!!! 
			//	   => ������ �ƴ϶�.. �׳�.. foo(int)�� �������.!!
			//	   => foo(...) ���� ��밡��..
}