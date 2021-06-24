// 그 외. compile options
// vs 2017, 2019 : C++14 문법기준 컴파일
// g++10.x       : C++14 문법기준 컴파일

// C++17 이상의 문법을 사용하려면
// g++ 소스이름.cpp  -std=c++17   또는 -std=c++20
// cl  소스이름.cpp  /std:c++17   또는 /std:c++latest

// C++20 기술을 사용하려면
// VS 2019 Preview 설치 필요
// g++10.2

#include <functional>	// std::invoke

class Dialog
{
public:
	void Close() {}	// void Close(Dialog* this) {}
	static void Close2() {}
	void Close3(int a) {}	// void Close3(Dialog* this, int a) {}
};

void foo() {} 
void foo2(int a) {} 

// Member method와 function pointer
// 핵심 1. 일반 Function pointer에 member method의 주소를 담을 수 없다.
// 핵심 2. 일반 Function pointer에 static member method의 주소를 담을 수 있다.
// 핵심 3. Member method에 대한 member function pointer를 만들고 호출 하는 방법
// 핵심 4. std::invoke() 함수
int main()
{
	void (*f1)() = &foo;				
	// void (*f2)() = &Dialog::Close;	// error: this 가 전달되는 함수
	void (*f3)() = &Dialog::Close2;

	// Member method의 주소를 담는 function pointer를 만드는 방법
	void (Dialog::*f2)() = &Dialog::Close;
	// f2();	// error: member method를 가리키므로, 호출시, this가 전달되어야 한다. - this call

	Dialog dlg;
	// dlg.f2();	// error: Dialog 에서 f2라는 이름의 함수를 찾게 된다.

	// dlg.*f2();		// .* : Pointer to member 라는 이름을 가진 연산자 C++ only
					// error: 연산자 우선순위 문제

	(dlg.*f2)();	// OK: 이 표기법이 member function pointer를 호출하는 방법!

	f3();
	// f2(&dlg);	// error: but...이렇게 되면 좋지 않을까? 결국 this를 전달하는 표기법이므로
				// unirom call syntax
	// 위 문법 대신 C++17에서 std::invoke 등장
	std::invoke(f1);	// 일반 function 호출
	void (*f4)(int) = &foo2;
	std::invoke(f4, 10);	// f4(10) 인자가 있다면 이렇게...

	std::invoke(f2, &dlg);		// (dlg.*f2)()
	void (Dialog::*f5)(int) = &Dialog::Close3;
	std::invoke(f5, &dlg, 10);	// (dlg.*f5)(10)

}
