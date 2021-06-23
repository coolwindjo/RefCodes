// unevaluated1.cpp
#include <iostream>

// 핵심 
// 평가되지 않은 표현식(unevaluated expression)

int foo(int a, int b); // { return 0; }

int main()
{
	int a = 0;

	// sizeof : 함수가 아닌 연산자, 컴파일 시간에 크기를 구하는 것.
	int n1 = sizeof(a);		// 4
	int n2 = sizeof(int);	// 4
	int n3 = sizeof(&foo);	// 4 - 함수주소의 크기(즉, 포인터 타입의 크기)

//	int n4 = sizeof(foo);	// error. - 함수 자체의 크기는 구할수 없다.
							// 이유 - 컴파일러는 함수 선언만으로도 함수를 호출할수 있는데
							// 함수의 크기를 구하려면 "완벽한 구현이 제공" 되어야 한다.

	// 핵심 : sizeof(함수호출식) :함수호출의 결과로 나오는 타입의 크기.
	int n5 = sizeof( foo(1, 2) ); // foo의 반환 타입인 int의 크기 - 4

	// 평가되지 않은 표현식(unevaluated expression)
	// => 함수 호출식 같은 표현식이 실제로는 실행되지 않고, 컴파일 시간에만 활용되는것
	// 4개가 있습니다. ( sizeof, noexcept, decltype, typeid)
	bool b = noexcept( foo(1, 2 ) );
	decltype(foo(1, 2)) d1;
	std::cout << typeid(foo(1, 2)).name() << std::endl;

}








