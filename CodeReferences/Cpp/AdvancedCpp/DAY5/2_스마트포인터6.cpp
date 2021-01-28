#include <iostream>

class Car
{
public:
	void Go() { std::cout << "Go" << std::endl; }
	~Car() { std::cout << "~Car" << std::endl; }
};

// C++ ǥ�� ����Ʈ�����͸� ����Ϸ���
#include <memory>

int main()
{
	std::shared_ptr<Car> sp1(new Car); // ��������� ����.
	std::shared_ptr<Car> sp2 = sp1; // �̼��� ������� ����

	// 1. ũ��
	std::cout << sizeof(sp1) << std::endl; // 8 (32��Ʈ ȯ��)

	// 2. .�� -> ������

	// -> : ���ü(Car) �� ��� ����
	sp1->Go();

	// . : shared_ptr ��ü�� �Լ� ���.
	int cnt = sp1.use_count(); // ���� ��������� ī��Ʈ.. 2
	sp1.reset(); // sp1 = nullptr �� �ǹ�.
}



// ���� �ҽ��� ī�信 �ֽ��ϴ�.