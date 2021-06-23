#include <iostream>

class Car
{
public:
	void Go() { std::cout << "Go" << std::endl; }
	~Car()    { std::cout << "~Car" << std::endl; }
};
// ���� : ��ü�� �ٸ� Ÿ���� ������ ó�� ���Ǵ� ��
// �������� : -> �����ڿ� * �����ڸ� ������ �ؼ� ������ ó�� ���̰� �ϴ� ��.
// ���� : ��ü�̹Ƿ� ����/����/����/�Ҹ��� ��� ������ �����Ҽ� �ִ�.
//			Ư��, �Ҹ��ڿ��� �ڵ� ���� ���..
// �ٽ��� �Ʒ� Ŭ���� �Դϴ�.
class Ptr
{
	Car* obj;
public:
	Ptr(Car* p = 0) : obj(p) {}
	~Ptr() { delete obj; }
	Car* operator->() { return obj; }
	Car& operator*() { return *obj; }
};

int main()
{
	Ptr p = new Car;  // Ptr p( new Car )

	p->Go(); // p.operator->() Go() �ε�
			// (p.operator->())->Go() ó�� �ؼ��˴ϴ�.
			// 1000->Go()
	(*p).Go();
}


