#include <iostream>

// 2������ ���� Mul�� ����ǥ�������� ����� ���ô�.
//auto f1 = [](int a, int b) { return a * b; }; // C++11

//auto f1 = [](auto a, auto b)  { return a * b; }; // C++14
//  template<typename T1, typename T2> auto operator()(T1 a, T2 b) {return a * b;}

auto f1 = [](auto a, decltype(a) b) { return a * b; }; 

// �׷��� C++20 ������ ����ǥ���Ŀ��� ���ø� ����� ���������ϴ�.
auto f1 = []<typename T> (T a, T b) { return a * b; }; // C++20 ǥ���


int main()
{
	std::cout << f1(1, 2)     << std::endl;
	std::cout << f1(1.2, 2.2) << std::endl;

	std::cout << f1(1,   2.2) << std::endl;

	// �׷���... 1, 2��° ���ڰ� ������ ���� �Ҽ� ������ ?
	// swap(a, b) ���� ���鶧�� a,b �� ���� ���� �����ؾ� �Ѵ�.
}

