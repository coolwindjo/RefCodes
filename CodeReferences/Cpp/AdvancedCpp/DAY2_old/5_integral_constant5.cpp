#include <iostream>

// C++11 ǥ�� ���鶧 int2type�� ���� ���Ѽ� �Ʒ� ���ø��� �����մϴ�.
/*
template<typename T, T N> struct integral_constant
{
	static constexpr T value = N;
};

// �Ʒ� 3�ٿ��� ��� ������ �ٸ� Ÿ�� �Դϴ�.
integral_constant<int, 0> n0;
integral_constant<int, 1> n1;
integral_constant<short, 0> s0;

// C++11 �ٽ�.
// true/false : �������� ��Ÿ���� "��" ���� Ÿ��.
// true_type, false_type : �������� ��Ÿ���� Ÿ��.
typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true>  true_type;

//------------------------------------
// is_pointer�� ���鶧 �Ʒ� ó�� ��������ϴ�.
template<typename T> struct is_pointer     : false_type {};  // value = false
template<typename T> struct is_pointer<T*> : true_type {};   // value = true
*/

#include <type_traits> // �� �ڵ尡 ���⿡ �ֽ��ϴ�.


template<typename T> void printv_imp(const T& v, std::true_type ) { std::cout << v << " : " << *v << std::endl; }
template<typename T> void printv_imp(const T& v, std::false_type ) { std::cout << v << std::endl; }


template<typename T> void printv(const T& v)
{
	printv_imp(v, std::is_pointer<T>() );

}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
