#include <iostream>

struct Base
{
	int value = 10; 
};
struct Derived : public Base
{
	int value = 20;
};
int main()
{
	Derived d;
	std::cout << d.value << std::endl; // 20

	// �Ʒ� 2���� �������� ����� ?
	std::cout << static_cast<Base>(d).value << std::endl; // 10
	std::cout << static_cast<Base&>(d).value << std::endl; // 10

	//static_cast<Base>(d).value = 30;// error
	static_cast<Base&>(d).value = 30;// ok
}
// �ٽ�. �ӽð�ü��
// 1. ����ڰ� ���� ����⵵ �ϰ� -- �Լ� ���ڷ� ����  foo( Point(1,2))
// 2. ����ڰ� �ڵ尡 ����ɶ� �ڵ����λ����Ǳ⵵ �մϴ�.
//   A. ���� ��ȯ�ϴ� �Լ�
//   B. �� Ÿ�� ���� ĳ����.
//    => ���, ����� ���� Ÿ���� ��� �ǵ��� "�� ĳ����"�� ������� ������.





