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
				// &obj �ּҿ��� B�� ã�ƶ�!!
				// ã���� ������ error
				// ã�� ��� B�� �ּ� ��ȯ.. 
				// &obj�� �ٸ��� �ִ�.
				// &obj + sizeof(A)

	//B* pB = reinterpret_cast<B*>(&obj); // 1000
				// &obj �� ������ Bó�� ����

	//pB->b = 100; // ccc �� ���忡���� ccc.a = 100 �� �ǹ�.

	std::cout << &obj << std::endl; // 1000
	std::cout << pA << std::endl;   // 1000
	std::cout << pB << std::endl;   // 1004

	obj.fc(); // 1000
	obj.fa(); // 1000
	obj.fb(); // 1004
}




