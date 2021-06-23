// 3_forward8
#include <vector>
#include <type_traits>
template<typename T> class List
{
public:
	List(int sz, T value) {}

	template<typename C>
	//List(C c) {}	// call by value : 복사본의 오버헤드
	//List(C& c) {}	// call by reference : 임시객체 받을수 없다.
	//List(const C& c) {} // const lvalue reference : move 가 안됨.
	List(C&& c) {}
};
template<typename C>
//List(C&& c)->List< typename C::value_type >; // vector<int>&::value_type 하는 코드 라서 에러.
List(C&& c)->List< typename std::remove_reference_t<C>::value_type >;


int main()
{
	List  s1(10, 3);  
	
	std::vector<int> v = { 1,2,3 };


	List s2(v); // v 는 lvalue 이므로
				// C의 타입은 : "vector<int>" 가 아니고, "vector<int>&" 입니다.


//	f4(n); // T : int& 


	List s3(std::vector<int>{1, 2, 3}); // 임시객체
}

/*
struct A
{
	typedef int value_type;
};
A::value_type n; // ok
A&::value_type n; // error
*/

// 컴파일 옵션 : /std:c++latest 추가하세요..