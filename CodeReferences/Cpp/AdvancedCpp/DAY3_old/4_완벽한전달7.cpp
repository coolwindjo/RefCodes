#include <iostream>
#include <functional>

// ���. �Ϻ��� ���� �ڵ�� ��κ�
// 1. ��ȯ Ÿ���� decltype(auto) �� ��찡 �����ϴ�.
// 2. ���ڸ� �������� T&& ... args  �����Դϴ�.
// 3. �ٸ� ���� ���ڸ� �������� std::forward<T>(args)... �� ��� ����

class Test
{
public:
	void foo(int a, int b) {}
};

template<typename F, typename ... T>
decltype(auto) chronometry(F f, T&& ... arg)
{
//	return f(std::forward<T>(arg)...); // (obj.*f)(10,20)
	return std::invoke(f, std::forward<T>(arg)...);  // C++17
}

int main()
{
/	chronometry(�Ϲ��Լ�, 10, 20);
	Test t;
	chronometry( &Test::foo, &t, 10, 20); //  t.foo(10,20)
}
