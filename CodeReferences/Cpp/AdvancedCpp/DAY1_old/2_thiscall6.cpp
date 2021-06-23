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
	// �Լ� �������� ũ��� �׻� 4�̴�... - C������ �°� C++�� Ʋ��

	// ���߻���� ����Լ� �����ʹ� ũ�Ⱑ 8�̴�.
	void(C::*f)();  // { �Լ��ּ� 4����Ʈ, this offset�� 4����Ʈ }
	
	std::cout << sizeof(f) << std::endl;

	// C++ member function pointer size

//	f = &C::fa; // { fa ���ּ�, this�� offset = 0}
	f = &C::fb; // { fb ���ּ�, this�� offset = sizeof(A), 4}

	C obj;
	obj.fc();	// fc(&obj);  1000

	(obj.*f)();	// f�� fa �� �ּҸ� ���� ��� : 1000����
				// f�� fb �� �ּҸ� ���� ��� : 1004���� ���;� �մϴ�.
				// f(&obj) ���ٵ�.. ��� ����� �����ұ� ?

				// f.�Լ��ּ�( &obj + f.this_offset ) ���� ȣ��

}




