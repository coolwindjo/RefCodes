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
#if 0
	B* pB = &obj;						// 1004
#else
	#if 0
	B* pB = (B*)&obj;					// 1004
	#else
		#if 1
	B* pB = static_cast<B*>(&obj);		// 1004
	// &obj 주소에서 B를 찾아라!
	// 찾을 수 없으면 Error!
	// 찾은 경우, B의 주소를 반환
	// &obj 와 다를 수 있다.
	// &obj + sizeof(A)
		#else
	B* pB = reinterpret_cast<B*>(&obj);	// 1000
	// &obj를 무조건 B처럼 생각
		#endif
	#endif
#endif
	std::cout << &obj << std::endl;	// 1000
	std::cout << pA << std::endl;	// 1000
	std::cout << pB << std::endl;	// 1004

	obj.fc();	// 1000
	obj.fa();	// 1000
	obj.fb();	// 1004
}




