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
	// (x86에서)
	// Function Pointer의 크기는 항상 4 이다. => C: 맞음, C++: 틀림
	// 다중상속의 Member Function Pointer는 크기가 2배이다.
	void(C::*f)();	// {함수주소 4 byte, this offset 값 4 byte}
	// Refer to "c++ member function pointer size"
	// https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible

	std::cout << sizeof(f) <<std::endl;

	/*/
	f = &C::fa;		// { fa 주소, this offset = 0 }
	/*/
	f = &C::fb;		// { fb 주소, this offset = sizeof(A) }
	//*/

	C obj;
	obj.fc();	// fc(&obj);	1000

	(obj.*f)();	// f 가 &fa 의 주소를 담은 경우: 1000
				// f 가 &fb 의 주소를 담은 경우: 1004
				// f(&obj) 일텐데... 어떻게 B 영역의 주소를 가져올까?
				// f.함수주소( &obj + f.this_offset ) 으로 호출

}




