#include <iostream>

struct A
{
	int a;
	void fa() { std::cout << "fa : " << this << std::endl; }
};
struct B
{
	int b;
	void fb() { std::cout << "fb : " << this << std::endl; }
};
struct C : public A, public B
{
	int c;
	void fc() { std::cout << "fc : " << this << std::endl; }
};

int main()
{
	// 함수 포인터의 크기는 항상 4이다... - C에서만 맞고 C++은 틀림

	// 다중상속의 멤버함수 포인터는 크기가 8이다.
	void(C::*f)();  // { 함수주소 4바이트, this offset값 4바이트 }
	
	std::cout << sizeof(f) << std::endl;

	// C++ member function pointer size

//	f = &C::fa; // { fa 의주소, this의 offset = 0}
	f = &C::fb; // { fb 의주소, this의 offset = sizeof(A), 4}

	C obj;
	obj.fc();	// fc(&obj);  1000

	(obj.*f)();	// f가 fa 의 주소를 담은 경우 : 1000번지
				// f가 fb 의 주소를 담은 경우 : 1004번지 나와야 합니다.
				// f(&obj) 일텐데.. 어떻게 제대로 동작할까 ?

				// f.함수주소( &obj + f.this_offset ) 으로 호출

}




