// 1_move11_2
#include <iostream>
#include <string>
#include <type_traits>

template<typename T, typename U> struct pair
{
	T first;
	U second;

//	pair(const T& a, const U& b) : first(a), second(b) {}
//	pair(T&& a, U&& b) : first(std::move(a)), second(std::move(b)) {}

	// setData�� ��� ���ڰ� �Ѱ� �̹Ƿ� 2���� setter�� �����ϸ� ������
	// pair�� ��� 4���� ������ �ʿ�!!

	// "forwarding reference"�� ����.

//	template<typename A, typename B> 
//	pair(A&& a, B&& b) : first(std::forward<A>(a) ), second(std::forward<B>(b)) {}

	// �Ʒ� �ڵ��� ������
	// �Ϲ� �Լ��� "��ȯ Ÿ��"�� ������
	// �����ڴ� "��ȯ Ÿ���� �����ϴ�."
//	template<typename A, typename B> 
//	std::enable_if_t< std::is_constructible_v<A, T> && std::is_constructible_v<B, U> >
//	pair(A&& a, B&& b) : first(std::forward<A>(a) ), second(std::forward<B>(b)) {}

	/*
	template<typename A, 
		     typename B, 
	std::enable_if_t< std::is_convertible_v<A, T> && std::is_convertible_v<B, U> , int> = 0 >
	pair(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}
	*/

	// ���� ���̺귯�� �����ڵ��� ������, ���������, ���Կ����� ���� ���鶧
	// ���ܰ� ������ �� noexcept�� ���Դϴ�.
	template<typename A,
		     typename B,
		     std::enable_if_t< std::is_convertible_v<A, T> && std::is_convertible_v<B, U>, int> = 0 >
	pair(A&& a, B&& b) noexcept ( std::is_nothrow_constructible_v<T> && 
								  std::is_nothrow_constructible_v<U> ) 
		: first(std::forward<A>(a)), second(std::forward<B>(b)) {}

};

int main()
{
	std::string s1 = "ABCD";
	std::string s2 = "ABCD";

	pair<std::string, std::string> p1(s1, std::move(s2));

//	pair<std::string, std::string> p2(1, 3.4); // �� ����� ������ ������ ���ô�.
									// 1. pair(int, double) ������ �����ڰ� C++ �ڵ�� ����
									// 2. (1)���� ���� ������ �ڵ带 ������ �Ҷ� ����..
									//    "first(1)" �ڵ尡 ������ ����
									
									// enable_if ������ ����ϸ�
									// �̼��� pair(int, double) ������ ������ ��ü�� ���� �ȵ�.

	std::cout << s1 << std::endl; // "ABCD";
	std::cout << s2 << std::endl; // "";
}





