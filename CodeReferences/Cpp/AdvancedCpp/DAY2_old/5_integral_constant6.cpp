#include <iostream>

#include <type_traits>

template<typename T> void foo(T a)
{
	// T의 포인터 여부에 따라 다른 알고리즘을 작성하고 싶다.
	// 방법 1. if 문사용

	if  (std::is_pointer_v<T>)
	{
		//....
		// 단, "*a" 표기법은 사용할수 없다. 
	}
	else
	{
		//....
	}
	// 방법 2. "*a" 표기법이 필요 했다면... true_type/false_type을 사용한 함수 오버로딩사용
	foo_imp(a, std::is_pointer<T>());
}
template<typename T> void foo_imp(T a, std::true_type) { }  // 포인터 인경우
template<typename T> void foo_imp(T a, std::false_type) { } // 포인터가 아닌 경우



int main()
{

}