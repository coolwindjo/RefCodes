#include <functional>  // std::invoke
// 멤버 함수와 함수 포인터
// 1. 일반 함수포인터에 멤버 함수의 주소를 담을수 없다.
// 2. 일반 함수포인터에 static 멤버 함수의 주소를 담을수 있다.
// 3. 멤버 함수에 대한 함수 포인터를 만들고 사용하는 방법.
// 4. std::invoke() 함수
// 5. C++17 이상의 문법을 사용하기 위한 컴파일러 옵션..
class Dialog
{
public:
	void Close() {} // void Close(Dialog* this) {}
	static void Close2() {}
};
void foo() {} 

int main()
{
	void(*f1)() = &foo;				// ok		
//	void(*f2)() = &Dialog::Close;	// error. this가 전달되는 함수..
	void(*f3)() = &Dialog::Close2;  // ok..   


	// 멤버 함수의 주소를 담는 함수 포인터를 만드는 방법.
	void(Dialog::*f2)() = &Dialog::Close;

//	f2(); // f2는 멤버 함수를 가리키므로 호출시, this가 전달되어야 한다. this call
		  // 이 표기법은 this가 없으므로 error

	Dialog dlg;
	//dlg.f2(); // error. Dialog 에서 f2라는 이름의 함수를 찾게된다. 
	//dlg.*f2();  // .* : Pointer to member 라는 이름을 가진 연산자. C++ 전용
				// error. 연산자 우선순위 문제..

	(dlg.*f2)(); // ok. 이 표기법이 멤버 함수 포인터를 가지고
				// 함수를 호출하는 방법.

	f1();        // 일반 함수 포인터로 함수 호출
	(dlg.*f2)(); // 멤버 함수 포인터로 함수 호출
//	f2(&dlg);    // 이렇게 되면 좋지 않을까 ? 결국 this를 전달하는 표기법이므로
				// uniform call syntax 

	// 위 문법 대신 C++17 에서 std::invoke 등장..
//	std::invoke(f1);     // f1()  일반 함수 호출
//	std::invoke(f1, 10); // f1(10) 인자가 있다면 이렇게.. 

	std::invoke(f2, &dlg);			// (dlg.*f2)()
//	std::invoke(f2, &dlg, 10, 20);  // (dlg.*f2)(10,20)
}
// vs 2017, 2019 : C++14 문법기준 컴파일
// g++10.x       : C++14 문법기준 컴파일

// C++17 이상의 문법을 사용하려면
// g++ 소스이름.cpp  -std=c++17   또는 -std=c++20
// cl  소스이름.cpp  /std:c++17   또는 /std:c++latest













