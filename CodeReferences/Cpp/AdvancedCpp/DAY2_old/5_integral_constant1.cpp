#include <iostream>
#include <type_traits>

// �������� ���� 
template<typename T> void printv_pointer(const T& v)
{
	std::cout << v << " : " << *v << std::endl;
}
// �����Ͱ� �ƴ� ���� �и�.
template<typename T> void printv_not_pointer(const T& v)
{
	std::cout << v <<  std::endl;
}

template<typename T> void printv(const T& v)
{
	if (std::is_pointer_v<T>) // ���Ⱑ ������ �ð��� false ��
		printv_pointer(v);	  // �� �Լ� ���ø��� C++ �ڵ�� �����˴ϴ�.
	else
		printv_not_pointer(v);
}

int main()
{
	int n = 10;
	printv(n); 
	
}
