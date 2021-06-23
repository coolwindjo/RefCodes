#include <vector>
#include <iostream>
// Effective Modern C++
// Effective C++ 3/e,  More Effective C++
int main()
{
	std::vector<int>  v1 = { 1,1,1 };
	std::vector<bool> v2 = { 1,1,1 };

	// a1�� a2�� Ÿ���� ������ ������
	auto a1 = v1[0]; // int a1 = v1[0]
	auto a2 = v2[0]; // BitProxy ���� Ŭ���� a2 = v2[0]

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;

	// �Ʒ� �ڵ� ������ ������
	auto& r1 = v1[0]; //  ok.. operator[] �����ڰ� ���� ��ȯ
	//auto& r2 = v2[0]; //  error. operator[] �� �ӽð�ü(rvalue)��ȯ.
	auto&& r3 = v2[0]; // ok

	//for (auto& n : v2) {}// error
}
