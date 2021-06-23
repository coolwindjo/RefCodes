#include <iostream>

class Test;		// Ŭ���� ���� ����..
				// ������ ������ ���, ������ Ÿ���� ��밡��

				// �ҿ����� Ÿ��(incomplete type )
				// incompete Ÿ���� delete �ÿ� �Ҹ��ڰ� ȣ����� �ʴ´�.
// Test* p; // ok
// Test  t; // error. ������ ���� �ʿ�

// "checked delete" ����
void foo(Test* p)
{
//	enum { type_must_be_complete = sizeof(Test) }; // ����ȭ�� �����ϱ� ���� sizeof
												   // ��ȯ�� �ޱ�

	// C++11 ���� ��Ÿ��
	static_assert(sizeof(Test) > 0, "delete incomplete type");

	delete p;
}



class Test
{
public:
	Test()  { std::cout << "Test()" << std::endl; }
	~Test() { std::cout << "~Test()" << std::endl; }
};

int main()
{
	Test* p = new Test;
	foo(p);
}
