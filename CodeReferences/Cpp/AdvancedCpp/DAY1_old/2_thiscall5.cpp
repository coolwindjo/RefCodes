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
	C obj;
	A* pA = &obj;
	//B* pB = &obj; // 1004

	//B* pB = (B*)&obj; // 1004

	//B* pB = static_cast<B*>(&obj); // 1004
				// &obj 주소에서 B를 찾아라!!
				// 찾을수 없으면 error
				// 찾은 경우 B의 주소 반환.. 
				// &obj와 다를수 있다.
				// &obj + sizeof(A)

	//B* pB = reinterpret_cast<B*>(&obj); // 1000
				// &obj 를 무조건 B처럼 생각

	//pB->b = 100; // ccc 의 입장에서는 ccc.a = 100 의 의미.

	std::cout << &obj << std::endl; // 1000
	std::cout << pA << std::endl;   // 1000
	std::cout << pB << std::endl;   // 1004

	obj.fc(); // 1000
	obj.fa(); // 1000
	obj.fb(); // 1004
}




