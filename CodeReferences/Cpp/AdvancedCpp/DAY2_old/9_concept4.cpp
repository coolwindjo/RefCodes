// 9_concept4.cpp
#include <iostream>
#include <type_traits>

// std::is_integral_v<T> : type_tratis, Ÿ�� �Ӽ� ����, ���ø� �κ� Ư��ȭ �������
// integral              : concept ����. Ÿ���� ������ �Ǵ� ������ ���.
//							���� ���� ������ �����ϴ� �Լ��� ���õ�
template<typename T> 
concept integral = std::is_integral_v<T>;

//template<typename T> requires std::is_integral_v<T>
template<typename T> requires integral<T>  // && ����2<T>
void foo(T a) {}

int main()
{
	bool b1 = integral<int>;
	bool b2 = integral<double>;

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
}
