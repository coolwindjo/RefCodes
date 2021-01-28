#include <iostream>

int& foo(int a, int b, int& c) 
{
	c = 200; 
	return c; 
}

// �Ϻ��� ������ ��κ� "�������� ���ø�" ����� ����մϴ�.
template<typename F, typename ... T> 
// auto chronometry(F f, T&& ... arg)  // ��ȯ Ÿ���� ������ ��� ������ ������ Ÿ������ �߷�
// auto chronometry(F f, T&& ... arg) -> decltype( f(std::forward<T>(arg)...) )
decltype(auto) chronometry(F f, T&& ... arg)
{
	return f(std::forward<T>(arg)... ); 
}

int main()
{
	int n = 10;

	int& ret = chronometry(foo, 10, 20, n); 

	std::cout << n << std::endl;
}
