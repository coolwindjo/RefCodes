#include <iostream>
#include <type_traits>

// 포인터인 경우와 
template<typename T> void printv_pointer(const T& v)
{
	std::cout << v << " : " << *v << std::endl;
}
// 포인터가 아닌 경우로 분리.
template<typename T> void printv_not_pointer(const T& v)
{
	std::cout << v <<  std::endl;
}

template<typename T> void printv(const T& v)
{
	if (std::is_pointer_v<T>) // 여기가 컴파일 시간에 false 라도
		printv_pointer(v);	  // 이 함수 템플릿은 C++ 코드로 생성됩니다.
	else
		printv_not_pointer(v);
}

int main()
{
	int n = 10;
	printv(n); 
	
}
