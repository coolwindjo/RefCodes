// reference_counting1
#include <iostream>
#include <vector>

class Car
{
	int speed;
public:
	~Car() { std::cout << "~Car" << std::endl; }
};
std::vector<Car*> v;

void foo()
{
	Car* p = new Car;

	v.push_back(p);

	// ���⼭�� ���̻� p�� �ʿ� �����ϴ�.
	// �޸𸮸� �����ص� �ɱ�� ?
	delete p;
}

int main()
{
	foo();
}