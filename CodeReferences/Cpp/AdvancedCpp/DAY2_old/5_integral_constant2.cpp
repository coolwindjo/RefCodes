#include <iostream>
#include <type_traits>

template<typename T> void printv_imp(const T& v,  YES )
{
	std::cout << v << " : " << *v << std::endl;
}

template<typename T> void printv_imp(const T& v, NO)
{
	std::cout << v << std::endl;
}

template<typename T> void printv(const T& v)
{
	// T�� ������ ���ο� ���� Dispatch( �Լ� �����ε� ���� Ȱ��)
	printv_imp(v, std::is_pointer_v<T>  );
				//  T�� ������     : true (1)
				//  T�� �����;ƴ� : false (0)
}

int main()
{
	int n = 10;
	printv(n);

}
