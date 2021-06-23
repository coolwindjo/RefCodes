#include <functional>  // std::invoke
// ��� �Լ��� �Լ� ������
// 1. �Ϲ� �Լ������Ϳ� ��� �Լ��� �ּҸ� ������ ����.
// 2. �Ϲ� �Լ������Ϳ� static ��� �Լ��� �ּҸ� ������ �ִ�.
// 3. ��� �Լ��� ���� �Լ� �����͸� ����� ����ϴ� ���.
// 4. std::invoke() �Լ�
// 5. C++17 �̻��� ������ ����ϱ� ���� �����Ϸ� �ɼ�..
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
//	void(*f2)() = &Dialog::Close;	// error. this�� ���޵Ǵ� �Լ�..
	void(*f3)() = &Dialog::Close2;  // ok..   


	// ��� �Լ��� �ּҸ� ��� �Լ� �����͸� ����� ���.
	void(Dialog::*f2)() = &Dialog::Close;

//	f2(); // f2�� ��� �Լ��� ����Ű�Ƿ� ȣ���, this�� ���޵Ǿ�� �Ѵ�. this call
		  // �� ǥ����� this�� �����Ƿ� error

	Dialog dlg;
	//dlg.f2(); // error. Dialog ���� f2��� �̸��� �Լ��� ã�Եȴ�. 
	//dlg.*f2();  // .* : Pointer to member ��� �̸��� ���� ������. C++ ����
				// error. ������ �켱���� ����..

	(dlg.*f2)(); // ok. �� ǥ����� ��� �Լ� �����͸� ������
				// �Լ��� ȣ���ϴ� ���.

	f1();        // �Ϲ� �Լ� �����ͷ� �Լ� ȣ��
	(dlg.*f2)(); // ��� �Լ� �����ͷ� �Լ� ȣ��
//	f2(&dlg);    // �̷��� �Ǹ� ���� ������ ? �ᱹ this�� �����ϴ� ǥ����̹Ƿ�
				// uniform call syntax 

	// �� ���� ��� C++17 ���� std::invoke ����..
//	std::invoke(f1);     // f1()  �Ϲ� �Լ� ȣ��
//	std::invoke(f1, 10); // f1(10) ���ڰ� �ִٸ� �̷���.. 

	std::invoke(f2, &dlg);			// (dlg.*f2)()
//	std::invoke(f2, &dlg, 10, 20);  // (dlg.*f2)(10,20)
}
// vs 2017, 2019 : C++14 �������� ������
// g++10.x       : C++14 �������� ������

// C++17 �̻��� ������ ����Ϸ���
// g++ �ҽ��̸�.cpp  -std=c++17   �Ǵ� -std=c++20
// cl  �ҽ��̸�.cpp  /std:c++17   �Ǵ� /std:c++latest













