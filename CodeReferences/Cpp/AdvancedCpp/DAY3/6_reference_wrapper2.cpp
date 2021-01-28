// 6_reference_wrapper1 - �� �˾� �μ���.. C++11�� ���Դµ�..
//								C++20���� ����� ������ ������ ����
#include <iostream>
#include <functional>

template<typename T> class reference_wrapper
{
	T* obj;
public:
	reference_wrapper(T& arg) : obj(&arg) {}

	// ��¥ ������ ��ȯ�ǰ�
	operator T&() { return *obj; }
};

int main()
{
	int n1 = 10;
	int n2 = 20;

	reference_wrapper<int> r1 = n1;
	reference_wrapper<int> r2 = n2;

	r1 = r2; // ���Կ�����..

	// r1�� ��¥ ������ ȣȯ�ǰ� ����.
	int& r3 = r1;  // r3.operator int&() 

	std::cout << n1 << std::endl;	
	std::cout << n2 << std::endl;	
	std::cout << r1 << std::endl;	
	std::cout << r2 << std::endl;	
}