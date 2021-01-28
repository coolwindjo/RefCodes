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

	// setData의 경우 인자가 한개 이므로 2개의 setter를 제공하면 되지만
	// pair의 경우 4개의 생성자 필요!!

	// "forwarding reference"가 좋다.

//	template<typename A, typename B> 
//	pair(A&& a, B&& b) : first(std::forward<A>(a) ), second(std::forward<B>(b)) {}

	// 아래 코드의 문제점
	// 일반 함수는 "반환 타입"이 있지만
	// 생성자는 "반환 타입이 없습니다."
//	template<typename A, typename B> 
//	std::enable_if_t< std::is_constructible_v<A, T> && std::is_constructible_v<B, U> >
//	pair(A&& a, B&& b) : first(std::forward<A>(a) ), second(std::forward<B>(b)) {}

	/*
	template<typename A, 
		     typename B, 
	std::enable_if_t< std::is_convertible_v<A, T> && std::is_convertible_v<B, U> , int> = 0 >
	pair(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}
	*/

	// 또한 라이브러리 설계자들은 생성자, 복사생성자, 대입연산자 등을 만들때
	// 예외가 없으면 꼭 noexcept를 붙입니다.
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

//	pair<std::string, std::string> p2(1, 3.4); // 이 경우의 현상을 생각해 봅시다.
									// 1. pair(int, double) 버전의 생성자가 C++ 코드로 생성
									// 2. (1)에서 만든 생성자 코드를 컴파일 할때 에러..
									//    "first(1)" 코드가 컴파일 실패
									
									// enable_if 버전을 사용하면
									// 이순간 pair(int, double) 버전의 생성자 자체가 생성 안됨.

	std::cout << s1 << std::endl; // "ABCD";
	std::cout << s2 << std::endl; // "";
}





