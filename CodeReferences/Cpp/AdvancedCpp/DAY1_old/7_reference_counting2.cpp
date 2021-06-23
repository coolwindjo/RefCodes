#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release() { if (--refCount == 0) delete this; }

	~Car() { std::cout << "~Car" << std::endl; }
};

int main()
{
	Car* p1 = new Car;
	p1->AddRef();	// ��Ģ 1. ��ü�� ����� ī��Ʈ ����

	Car* p2 = p1;
	p2->AddRef();	// ��Ģ 2. ��ü�� �ּҸ� �����ϸ� ī��Ʈ ����

	p2->Release();  // ��Ģ 3. ����� ���� ��� ����
	std::cout << "----" << std::endl;
	p1->Release();  // �̼��� ī��Ʈ�� 0�̹Ƿ� ��ü �ı�

}




