#include <iostream>

int a;		// ���� �̸� : a    Ÿ�� : int
	
int x[3];	// ���� �̸� : x	Ÿ�� : int[3]	
							// T[N] : bound array type
							// T[] : unbound array type


template<typename T> struct is_array
{
	static constexpr bool value = false;
	static constexpr int size = -1;
};
template<typename T, int N> struct is_array< T[N] >
{
	static constexpr bool value = true;
	static constexpr int size = N;
};

// C++20 ������ �迭�� ���ڷ� ������ ����ϴ� std::span  �̶�� ���� ���� ������ �ֽ��ϴ�.
template<typename T> void foo(const T& a)
{
	//   is_array<int[3]>::value 
	if ( is_array<T>::value )
		std::cout << "�迭. ũ��� " << is_array<T>::size  << std::endl;
	else
		std::cout << "�迭 �ƴ�" << std::endl;
}

int main()
{
	int x[3] = { 1,2,3 };
	foo(x);
}